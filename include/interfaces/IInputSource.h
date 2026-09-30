#pragma once
#include <Arduino.h>
#include "../models/SensorData.h"

class IInputSource
{
public:
    virtual void begin() = 0;
    virtual bool available() = 0;
    virtual void update() = 0;
    virtual SensorData read() = 0;
    virtual String getName() const = 0;

    virtual ~IInputSource() {}
};
