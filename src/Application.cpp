#include "../include/core/Application.h"
#include <Arduino.h>
#include "../include/config/Config.h"
#include "../include/services/DataValidator.h"

Application::Application()
    : game(TIME_MAX_GAME_MS),
      inputCount(0),
      outputCount(0)

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
    handleSerialCommands();
    for (int i = 0; i < inputCount; i++)
    {
        if (!inputs[i]->available())
            continue;

        SensorData data = inputs[i]->read();

        if (!DataValidator::isValid(data))
        {
            Serial.print("[REJET] Donnee invalide de ");
            Serial.println(data.getSource());
            continue;
        }

        for (int j = 0; j < outputCount; j++)
        {
            outputs[j]->send(data);
        }
        game.onButtonPressed(playerFromSource(data.getSource()));
    }
    game.update();
    printStateChange();
}

void Application::handleSerialCommands()
{
    if (!Serial.available())
        return;
    char c = Serial.read();
    if (c == 's')
        game.startRound();
    else if (c == 'r')
        game.reset();
}
void Application::printStateChange()
{
    if (!game.hasChanged())
        return;
    Serial.print("[ETAT] ");
    Serial.print(QuizStateMachine::stateToString(game.getState()));
    Serial.print(" | manche ");
    Serial.print(game.getRoundNumber());
    if (game.getState() == QuizState::GAGNANT)
    {
        Serial.print(" | gagnant : J");
        Serial.print(game.getWinner());
    }
    Serial.println();
}
int Application::playerFromSource(const String &source)
{
    if (source == "Joueur1")
        return 1;
    if (source == "Joueur2")
        return 2;
    return 0;
}