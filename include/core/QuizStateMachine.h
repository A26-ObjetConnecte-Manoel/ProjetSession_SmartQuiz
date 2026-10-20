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

class QuizStateMachine
{
private:
    void changeState(QuizState newState);

    QuizState state;
    int winner;
    int roundNumber;
    unsigned long roundStart;
    unsigned long dureeMax;
    bool changed;
    unsigned long stateStartTime;

public:
    QuizStateMachine(unsigned long dureeMaxManche);

    void startRound();
    void reset();
    void onButtonPressed(int joueur);
    void signalError();
    void update();

    QuizState getState() const;
    int getWinner() const;
    int getRoundNumber() const;
    bool hasChanged();

    static String stateToString(QuizState state);
};
