#include "../include/core/Application.h"
#include <Arduino.h>
#include "../include/config/Config.h"

Application::Application()
    : inputCount(0),
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

void Application::update()
{
    for (int i = 0; i < inputCount; i++)
    {
        if (inputs[i]->available())
        {
            SensorData data = inputs[i]->read();

            for (int j = 0; j < outputCount; j++)
            {
                outputs[j]->send(data);
            }

            Serial.printf(
                "Donnee invalide rejetee [%s] %s = %.2f %s\n",
                data.getSource().c_str(),
                data.getType().c_str(),
                data.getValue(),
                data.getUnit().c_str());
        }
    }
}