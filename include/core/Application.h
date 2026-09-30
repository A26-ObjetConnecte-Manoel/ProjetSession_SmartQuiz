#pragma once
#include "../interfaces/IInputSource.h"
#include "../interfaces/IOutputTarget.h"

const int MAX_INPUTS = 10;
const int MAX_OUTPUTS = 10;

class Application
{
private:
    IInputSource *inputs[MAX_INPUTS];
    IOutputTarget *outputs[MAX_OUTPUTS];

    int inputCount;
    int outputCount;

public:
    Application();

    void addInput(IInputSource *input);
    void addOutput(IOutputTarget *output);

    void begin();
    void update();
};
