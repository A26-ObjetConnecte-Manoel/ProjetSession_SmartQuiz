#include "../include/input/boutonInput.h"

Bouton::Bouton(int pin, unsigned long debounceDelay)
    : m_pin(pin),
      m_lastState(HIGH),
      m_debouncedState(HIGH),
      m_lastDebounceTime(0),
      m_debounceDelay(debounceDelay)
{
}

void Bouton::begin()
{
    pinMode(m_pin, INPUT_PULLUP);
    m_lastState = digitalRead(m_pin);
    m_debouncedState = m_lastState;
}

void Bouton::update()
{
    bool reading = digitalRead(m_pin);

    if (reading != m_lastState)
    {
        m_lastDebounceTime = millis();
    }

    if ((millis() - m_lastDebounceTime) >= m_debounceDelay)
    {
        m_debouncedState = reading;
    }

    m_lastState = reading;
}

bool Bouton::available()
{

    update();

    return (m_debouncedState == LOW);
}
SensorData Bouton::read()
{

    return SensorData(getName(), "bouton", 1.0f, "", millis());
}