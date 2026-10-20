#pragma once
#include "../interfaces/IInputSource.h"
#include "../interfaces/IOutputTarget.h"
#include "../services/QuizStateService.h"

const int MAX_INPUTS = 10;
const int MAX_OUTPUTS = 10;

class Application
{
private:
    IInputSource *inputs[MAX_INPUTS];
    IOutputTarget *outputs[MAX_OUTPUTS];
    QuizStateService &stateService;

    void updateCommands();
    void updateInputs();
    void updateState();
    void updateDiagnostics();
    static int playerFromSource(const String &source);

    int inputCount;
    int outputCount;
    unsigned long lastDiagnosticMs;
    unsigned long diagnosticIntervalMs;

public:
    Application(unsigned long diagnosticIntervalMs, QuizStateService &stateService);

    void addInput(IInputSource *input);
    void addOutput(IOutputTarget *output);

    void begin();
    void update();
};
