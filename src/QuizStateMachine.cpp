#include "../include/core/QuizStateMachine.h"

QuizStateMachine::QuizStateMachine(unsigned long dureeMaxManche)
    : state(QuizState::ATTENTE),
      winner(0),
      roundNumber(0),
      roundStart(0),
      dureeMax(dureeMaxManche),
      changed(true),
      stateStartTime(0)
{
}
void QuizStateMachine::startRound()
{
    if (state == QuizState::ATTENTE)
    {
        roundNumber++;
        roundStart = millis();
        changeState(QuizState::MANCHE);
    }
}
void QuizStateMachine::onButtonPressed(int joueur)
{
    if (state == QuizState::MANCHE)
    {
        if (joueur < 1 || joueur > 2)
        {
            return;
        }
        winner = joueur;
        changeState(QuizState::GAGNANT);
    }
}
void QuizStateMachine::reset()
{
    if (state == QuizState::MANCHE || state == QuizState::GAGNANT)
    {
        changeState(QuizState::REINITIALISATION);
    }
    else if (state == QuizState::ERREUR)
    {
        changeState(QuizState::ATTENTE);
    }
}
void QuizStateMachine::signalError()
{
    changeState(QuizState::ERREUR);
}
void QuizStateMachine::update()
{
    if (state == QuizState::MANCHE && (millis() - roundStart) >= dureeMax)
    {
        changeState(QuizState::REINITIALISATION);
    }
    else if (state == QuizState::REINITIALISATION && (millis() - stateStartTime) >= 1000)
    {
        winner = 0;
        changeState(QuizState::ATTENTE);
    }
}
void QuizStateMachine::changeState(QuizState newState)
{
    if (state != newState)
    {
        state = newState;
        stateStartTime = millis();
        changed = true;
    }
}
bool QuizStateMachine::hasChanged()
{
    if (changed)
    {
        changed = false;
        return true;
    }
    return false;
}
QuizState QuizStateMachine::getState() const
{
    return state;
}
int QuizStateMachine::getWinner() const
{
    return winner;
}
int QuizStateMachine::getRoundNumber() const
{
    return roundNumber;
}
String QuizStateMachine::stateToString(QuizState state)
{
    switch (state)
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