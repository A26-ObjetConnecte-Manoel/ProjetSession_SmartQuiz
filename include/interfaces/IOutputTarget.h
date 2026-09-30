#pragma once
#include <Arduino.h>
#include "../models/SensorData.h"

class IOutputTarget
{
public:
    virtual void begin() = 0;
    virtual bool send(const SensorData &data) = 0;
    virtual String getName() const = 0;

    virtual ~IOutputTarget() {}
};
