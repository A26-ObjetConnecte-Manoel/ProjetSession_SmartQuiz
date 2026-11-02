#pragma once
#include "../interfaces/IOutputTarget.h"

class SerialOutput : public IOutputTarget
{
public:
    SerialOutput();

    void begin() override;
    bool send(const SensorData &data) override;
    String getName() const override;
};
