#include "../include/output/SerialOutput.h"
#include <Arduino.h>

SerialOutput::SerialOutput()
{
}

void SerialOutput::begin()
{
    Serial.println("SerialOutput prêt.");
}

bool SerialOutput::send(const SensorData &data)
{
    Serial.print("[");
    Serial.print(data.getSource());
    Serial.print("] ");

    Serial.print(data.getType());
    Serial.print(" = ");
    Serial.print(data.getValue());
    Serial.print(" ");
    Serial.println(data.getUnit());

    return true;
}

String SerialOutput::getName() const
{
    return "SerialOutput";
}
