#include "../include/input/boutonInput.h"

Bouton::Bouton(int pin, String name, unsigned long debounceDelay)
    : pin(pin),
      name(name),
      lastState(HIGH),
      debouncedState(HIGH),
      pressed(false),
      lastDebounceTime(0),
      debounceDelay(debounceDelay)
{
}

void Bouton::begin()
{
    pinMode(pin, INPUT_PULLUP);
    lastState = digitalRead(pin);
    debouncedState = lastState;
}

void Bouton::update()
{
    bool reading = digitalRead(pin);

    if (reading != lastState)
        lastDebounceTime = millis();

    if ((millis() - lastDebounceTime) >= debounceDelay && reading != debouncedState)
    {
        debouncedState = reading;
        if (debouncedState == LOW)
            pressed = true;
    }

    lastState = reading;
}

bool Bouton::available()
{
    update();
    if (pressed)
    {
        pressed = false;
        return true;
    }
    return false;
}

SensorData Bouton::read()
{

    return SensorData(getName(), "bouton", 1.0f, "", millis());
}
String Bouton::getName() const
{
    return name;
}