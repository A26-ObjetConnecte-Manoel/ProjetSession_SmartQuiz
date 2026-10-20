#pragma once
#include <Arduino.h>

enum class QuizState
{
    ATTENTE,
    MANCHE,
    GAGNANT,
    REINITIALISATION,
    ERREUR
};

class QuizStateService
{
private:
    QuizState currentState;
    int winner;
    int roundNumber;
    unsigned long roundStartMs;
    unsigned long stateStartMs;
    unsigned long maxRoundMs;
    bool changed;

    void changeState(QuizState newState);

public:
    QuizStateService(unsigned long maxRoundMs);

    void startRound();
    void reset();
    void onButtonPressed(int player);
    void setError();
    void update();

    QuizState getState() const;
    String getStateName() const;
    int getWinner() const;
    int getRoundNumber() const;
    bool hasChanged();
    unsigned long getRemainingMs() const;
};