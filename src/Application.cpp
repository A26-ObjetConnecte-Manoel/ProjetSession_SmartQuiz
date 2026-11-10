#include "../include/core/Application.h"
#include <Arduino.h>
#include "../include/config/Config.h"
#include "../include/services/DataValidator.h"
#include "../include/services/JsonService.h"

Application::Application(unsigned long diagnosticIntervalMs, QuizStateService &stateService, MqttService &mqttService)
    : stateService(stateService),
      mqttService(mqttService),

      inputCount(0),
      outputCount(0),
      lastDiagnosticMs(0),
      diagnosticIntervalMs(diagnosticIntervalMs),
      lastStatePublishMs(0)

{
    for (int i = 0; i < MAX_INPUTS; i++)
    {
        inputs[i] = nullptr;
    }

    for (int i = 0; i < MAX_OUTPUTS; i++)
    {
        outputs[i] = nullptr;
    }
}
void Application::begin()
{
    Serial.println("Initialisation des entrées...");

    for (int i = 0; i < inputCount; i++)
    {
        Serial.print("- ");
        Serial.println(inputs[i]->getName());

        inputs[i]->begin();
    }

    Serial.println("Initialisation des sorties...");

    for (int i = 0; i < outputCount; i++)
    {
        Serial.print("- ");
        Serial.println(outputs[i]->getName());

        outputs[i]->begin();
    }
}
void Application::addInput(IInputSource *input)
{
    if (inputCount < MAX_INPUTS)
    {
        inputs[inputCount] = input;
        inputCount++;
    }
}
void Application::addOutput(IOutputTarget *output)
{
    if (outputCount < MAX_OUTPUTS)
    {
        outputs[outputCount] = output;
        outputCount++;
    }
}

void Application::update()
{
    updateCommands();
    updateMqttCommands();
    updateInputs();
    updateState();
    updateDiagnostics();
}

void Application::updateCommands()
{
    if (!Serial.available())
        return;

    char c = tolower(Serial.read());

    if (c == 's')
        stateService.startRound();
    else if (c == 'r')
        stateService.reset();
    else if (c != '\n' && c != '\r')
    {
        Serial.print("[SmartQuiz] Commande inconnue: ");
        Serial.println(c);
    }
}
void Application::updateInputs()
{
    for (int i = 0; i < inputCount; i++)
    {
        if (inputs[i]->available())
        {
            SensorData data = inputs[i]->read();

            if (DataValidator::isValid(data))
            {
                stateService.onButtonPressed(playerFromSource(data.getSource()));
                for (int j = 0; j < outputCount; j++)
                {
                    outputs[j]->send(data);
                }
            }
            else
            {
                stateService.setError();
                Serial.println("[SmartQuiz] Donnee invalide rejetee.");
            }
        }
    }
}
void Application::updateState()
{
    stateService.update();

    if (stateService.hasChanged())
    {
        Serial.print("[SmartQuiz] Etat: ");
        Serial.print(stateService.getStateName());
        Serial.print(" | manche ");
        Serial.print(stateService.getRoundNumber());

        if (stateService.getState() == QuizState::GAGNANT)
        {
            Serial.print(" | gagnant: J");
            Serial.print(stateService.getWinner());
        }
        Serial.println();

        publishState();
    }
    else if (stateService.getState() == QuizState::MANCHE &&
             millis() - lastStatePublishMs >= STATE_REFRESH_MS)
    {
        publishState();
    }
}
void Application::publishState()
{
    lastStatePublishMs = millis();

    SensorData etat(
        "SmartQuiz",
        TYPE_ETAT,
        (float)stateService.getState(),
        stateService.getStateName(),
        millis());

    for (int j = 0; j < outputCount; j++)
    {
        outputs[j]->send(etat);
    }
}
void Application::updateDiagnostics()
{
    if (millis() - lastDiagnosticMs >= diagnosticIntervalMs)
    {
        lastDiagnosticMs = millis();

        Serial.println("[SmartQuiz] Systeme actif");
        Serial.print("[SmartQuiz] Entrees: ");
        Serial.println(inputCount);
        Serial.print("[SmartQuiz] Sorties: ");
        Serial.println(outputCount);
        Serial.print("[SmartQuiz] Etat: ");
        Serial.println(stateService.getStateName());
    }
}
void Application::updateMqttCommands()
{
    if (!mqttService.hasMessage())
        return;

    String topic = mqttService.getMessageTopic();
    String payload = mqttService.getMessagePayload();
    mqttService.clearMessage();

    // 1. Validation avant exécution
    Command command = JsonService::parseCommand(topic, payload);

    // 2. Exécution
    String statut = "ok";
    String message;

    if (command.type == CommandType::START)
    {
        if (stateService.startRound())
            message = "Manche demarree";
        else
        {
            statut = "refuse";
            message = "Manche deja en cours";
        }
    }
    else if (command.type == CommandType::RESET)
    {
        if (stateService.reset())
            message = "Manche reinitialisee";
        else
        {
            statut = "refuse";
            message = "Rien a reinitialiser";
        }
    }
    else if (command.type == CommandType::CONFIG)
    {
        stateService.setMaxRoundMs(command.dureeMaxS * 1000UL);
        message = "Duree maximale : " + String(command.dureeMaxS) + " s";
    }
    else
    {
        statut = "invalide"; // message rejeté, rien n'est modifié
        message = command.error;
    }

    // 3. Confirmation
    mqttService.publish(TOPIC_ACK, JsonService::buildAck(command.name, statut, message));

    Serial.print("[ACK] ");
    Serial.print(statut);
    Serial.print(" : ");
    Serial.println(message);
}
int Application::playerFromSource(const String &source)
{
    if (source == NOM_J1)
        return 1;
    if (source == NOM_J2)
        return 2;
    return 0;
}