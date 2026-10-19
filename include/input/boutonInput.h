#pragma once

#include <Arduino.h>
#include "../interfaces/IInputSource.h"

class Bouton : public IInputSource
{
private:
    int pin;

    bool lastState;
    bool debouncedState;
    bool pressed;

    unsigned long lastDebounceTime;
    unsigned long debounceDelay;

public:
    Bouton(int pin, unsigned long debounceDelay = 50);

    void begin() override;
    void update();
    bool available() override;
    SensorData read() override;
    String getName() const override;
};