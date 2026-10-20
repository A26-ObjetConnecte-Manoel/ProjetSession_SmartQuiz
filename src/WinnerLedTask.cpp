#include "../include/tasks/WinnerLedTask.h"

WinnerLedTask::WinnerLedTask(int pin, int player, const QuizStateService &stateService)
    : pin(pin),
      player(player),
      stateService(stateService)
{
}

void WinnerLedTask::begin()
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void WinnerLedTask::update()
{

    bool on = stateService.getState() == QuizState::GAGNANT &&
              stateService.getWinner() == player;

    digitalWrite(pin, on ? HIGH : LOW);
}