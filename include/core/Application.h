#pragma once
#include "../interfaces/IInputSource.h"
#include "../interfaces/IOutputTarget.h"
#include "QuizStateMachine.h"

const int MAX_INPUTS = 10;
const int MAX_OUTPUTS = 10;

class Application
{
private:
    IInputSource *inputs[MAX_INPUTS];
    IOutputTarget *outputs[MAX_OUTPUTS];
    QuizStateMachine game;

    void handleSerialCommands();
    void printStateChange();
    static int playerFromSource(const String &source);

    int inputCount;
    int outputCount;

public:
    Application();

    void addInput(IInputSource *input);
    void addOutput(IOutputTarget *output);

    void begin();
    void update();
};
