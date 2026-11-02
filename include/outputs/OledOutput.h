#pragma once

#include "../interfaces/IOutputTarget.h"
#include "../services/DisplayService.h"
#include "../services/QuizStateService.h"

class OledOutput : public IOutputTarget
{
private:
    DisplayService &display;
    const QuizStateService &stateService;

public:
    OledOutput(DisplayService &display, const QuizStateService &stateService);

    void begin() override;
    bool send(const SensorData &data) override;
    String getName() const override;
};