#include "../include/core/Application.h"
#include <Arduino.h>
#include "../include/config/Config.h"
#include "../include/services/DataValidator.h"

Application::Application(unsigned long diagnosticIntervalMs, QuizStateService &stateService)
    : stateService(stateService),
      inputCount(0),
      outputCount(0),
      lastDiagnosticMs(0),
      diagnosticIntervalMs(diagnosticIntervalMs)

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
    if (!stateService.hasChanged())
        return;
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
int Application::playerFromSource(const String &source)
{
    if (source == NOM_J1)
        return 1;
    if (source == NOM_J2)
        return 2;
    return 0;
}