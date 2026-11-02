#pragma once
#include <Arduino.h>
#include "../include/models/SensorData.h"

class JsonService
{

public:
    String toJson(const SensorData data, String stateName);
};