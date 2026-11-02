#include "../include/config/Config.h"
#include "../include/outputs/OledOutput.h"

OledOutput::OledOutput(DisplayService &display, const QuizStateService &stateService)
    : display(display),
      stateService(stateService)
{
}

void OledOutput::begin()
{
    display.begin();
}

bool OledOutput::send(const SensorData &data)
{
    if (!display.isReady())
        return false;

    if (data.getType() != TYPE_ETAT)
        return true;

    display.showGameState(
        stateService.getState(),
        stateService.getRoundNumber(),
        stateService.getWinner(),
        stateService.getRemainingMs());

    return true;
}

String OledOutput::getName() const
{
    return "OLED";
}