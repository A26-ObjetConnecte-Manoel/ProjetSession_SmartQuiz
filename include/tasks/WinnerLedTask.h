#pragma once
#include <Arduino.h>
#include "../services/QuizStateService.h"

class WinnerLedTask
{
private:
    int pin;
    int player;
    const QuizStateService &stateService;

public:
    WinnerLedTask(int pin, int player, const QuizStateService &stateService);

    void begin();
    void update();
};