#pragma once

#include "../interfaces/IOutputTarget.h"
#include "../services/MqttService.h"
#include "../services/QuizStateService.h"

class MqttOutput : public IOutputTarget
{
private:
    MqttService &mqttService;
    QuizStateService &stateService;
    const char *topic;
    int lastResultRound = 0;

public:
    MqttOutput(MqttService &mqttService, QuizStateService &stateService, const char *topic);

    void begin() override;
    bool send(const SensorData &data) override;
    String getName() const override;
};