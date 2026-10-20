#include "../include/services/QuizStateService.h"
#include "../include/config/config.h"

QuizStateService::QuizStateService(unsigned long maxRoundMs)
    : currentState(QuizState::ATTENTE),
      winner(0),
      roundNumber(0),
      roundStartMs(0),
      stateStartMs(0),
      maxRoundMs(maxRoundMs),
      changed(true)
{
}
void QuizStateService::startRound()
{
    if (currentState == QuizState::ATTENTE)
    {
        roundNumber++;
        roundStartMs = millis();
        changeState(QuizState::MANCHE);
    }
}
void QuizStateService::onButtonPressed(int player)
{
    if (currentState == QuizState::MANCHE)
    {
        if (player < 1 || player > 2)
        {
            return;
        }
        winner = player;
        changeState(QuizState::GAGNANT);
    }
}
void QuizStateService::reset()
{
    if (currentState == QuizState::MANCHE || currentState == QuizState::GAGNANT)
    {
        changeState(QuizState::REINITIALISATION);
    }
    else if (currentState == QuizState::ERREUR)
    {
        changeState(QuizState::ATTENTE);
    }
}
void QuizStateService::setError()
{
    changeState(QuizState::ERREUR);
}
void QuizStateService::update()
{
    if (currentState == QuizState::MANCHE && (millis() - roundStartMs) >= maxRoundMs)
    {
        changeState(QuizState::REINITIALISATION);
    }
    else if (currentState == QuizState::REINITIALISATION && (millis() - stateStartMs) >= REINIT_DURATION_MS)
    {
        winner = 0;
        changeState(QuizState::ATTENTE);
    }
}
void QuizStateService::changeState(QuizState newState)
{
    if (currentState != newState)
    {
        currentState = newState;
        stateStartMs = millis();
        changed = true;
    }
}
bool QuizStateService::hasChanged()
{
    if (changed)
    {
        changed = false;
        return true;
    }
    return false;
}
QuizState QuizStateService::getState() const
{
    return currentState;
}
int QuizStateService::getWinner() const
{
    return winner;
}
int QuizStateService::getRoundNumber() const
{
    return roundNumber;
}
String QuizStateService::getStateName() const
{
    switch (currentState)
    {
    case QuizState::ATTENTE:
        return "ATTENTE";
    case QuizState::MANCHE:
        return "MANCHE";
    case QuizState::GAGNANT:
        return "GAGNANT";
    case QuizState::REINITIALISATION:
        return "REINITIALISATION";
    case QuizState::ERREUR:
        return "ERREUR";
    default:
        return "INCONNU";
    }
}