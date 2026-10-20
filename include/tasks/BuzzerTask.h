#pragma once
#include <Arduino.h>
#include "../services/QuizStateService.h"

class BuzzerTask
{
private:
    int pin;
    const QuizStateService &stateService;

    QuizState lastState;
    bool active;
    unsigned long startMs;
    unsigned long durationMs;

    void beep(unsigned long ms);

public:
    BuzzerTask(int pin, const QuizStateService &stateService);

    void begin();
    void update();
};