#pragma once

#include <Arduino.h>
#include "../interfaces/IInputSource.h"

class Bouton : public IInputSource
{
private:
    int m_pin;

    bool m_lastState;
    bool m_debouncedState;

    unsigned long m_lastDebounceTime;
    unsigned long m_debounceDelay;

public:
    Bouton(int pin, unsigned long debounceDelay = 50);

    void begin() override;
    void update();
    bool available() override;
    SensorData read() override;
    String getName() const override;
};