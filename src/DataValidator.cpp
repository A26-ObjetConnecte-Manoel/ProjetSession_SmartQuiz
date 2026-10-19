
#include "../include/services/DataValidator.h"
#include <Arduino.h>

bool DataValidator::isValid(const SensorData &data)
{
    if (!isSourceValid(data.getSource()))
        return false;
    if (!isTimestampValid(data.getTimestamp()))
        return false;

    if (data.getType() == "bouton")
        return isButtonValid(data);

    return false;
}

bool DataValidator::isButtonValid(const SensorData &data)
{
    return data.getValue() == 1.0f;
}
bool DataValidator::isSourceValid(const String &source)
{
    return source.length() > 0;
}
bool DataValidator::isTimestampValid(unsigned long timestamp)
{
    return timestamp > 0;
}