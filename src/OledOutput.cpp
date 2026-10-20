#include "../include/config/Config.h"
#include "../include/output/OledOutput.h"

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

    // L'OLED affiche l'état du jeu : les appuis de boutons sont ignorés
    // (sinon l'appui de J2 après la victoire de J1 écraserait l'écran)
    if (data.getType() != TYPE_ETAT)
        return true;

    // Le SensorData d'état sert de signal ; les détails sont lus dans le service
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