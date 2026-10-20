#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "QuizStateService.h"

class DisplayService
{
private:
    Adafruit_SSD1306 &display;
    bool ready;

    void drawHeader(int round);

public:
    DisplayService(Adafruit_SSD1306 &display);

    void begin();
    bool isReady() const;
    void showMessage(const String &line1, const String &line2);
    void showGameState(QuizState state, int round, int winner, unsigned long remainingMs);
};