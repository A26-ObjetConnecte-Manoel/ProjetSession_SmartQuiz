#include "../include/config/Config.h"
#include "../include/tasks/BuzzerTask.h"

BuzzerTask::BuzzerTask(int pin, const QuizStateService &stateService)
    : pin(pin),
      stateService(stateService),
      lastState(QuizState::ATTENTE),
      active(false),
      startMs(0),
      durationMs(0)
{
}

void BuzzerTask::begin()
{
    pinMode(pin, OUTPUT);
    noTone(pin);
    lastState = stateService.getState();
}

void BuzzerTask::update()
{

    QuizState state = stateService.getState();

    if (state != lastState)
    {
        lastState = state;

        if (state == QuizState::MANCHE)
            beep(BIP_COURT_MS);
        else if (state == QuizState::GAGNANT)
            beep(BIP_VICTOIRE_MS);
    }

    if (active && millis() - startMs >= durationMs)
    {
        noTone(pin);
        active = false;
    }
}

void BuzzerTask::beep(unsigned long ms)
{

    tone(pin, BUZZER_FREQ_HZ);
    active = true;
    startMs = millis();
    durationMs = ms;
}