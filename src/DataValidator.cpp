#include "../include/config/Config.h"
#include "../include/services/DataValidator.h"
#include <Arduino.h>

bool DataValidator::isValid(const SensorData &data)
{
    if (!isSourceValid(data.getSource()))
        return false;
    if (!isTimestampValid(data.getTimestamp()))
        return false;
    if (data.getType() == "bouton")
    {
        if (!isButtonValid(data))
        {
            return false;
        }
        return isButtonValid(data);
    }
    return false;
}
bool DataValidator::isButtonValid(const SensorData &data)
{
    if (data.getValue() != 1.0f)
        return false;
    return true;
}
bool DataValidator::isSourceValid(const String &source)
{
    return source.length() > 0;
}
bool DataValidator::isTimestampValid(unsigned long timestamp)
{
    return timestamp > 0;
}