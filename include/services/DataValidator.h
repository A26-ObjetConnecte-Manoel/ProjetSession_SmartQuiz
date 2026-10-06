#pragma once

#include "../models/SensorData.h"

class DataValidator
{
public:
    static bool isValid(const SensorData &data);

private:
    static bool isButtonValid(const SensorData &data);
    static bool isSourceValid(const String &source);
    static bool isTimestampValid(unsigned long timestamp);
};