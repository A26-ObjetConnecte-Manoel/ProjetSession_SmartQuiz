#pragma once
#include "../config/config.h"
#include <Arduino.h>
#include "../interfaces/IInputSource.h"

class Bouton : public IInputSource
{
private:
    int pin;
    String name;

    bool lastState;
    bool debouncedState;
    bool pressed;

    unsigned long lastDebounceTime;
    unsigned long debounceDelay;

public:
    Bouton(int pin, String name, unsigned long debounceDelay = DEBOUNCE_DELAY);

    void begin() override;
    void update();
    bool available() override;
    SensorData read() override;
    String getName() const override;
};