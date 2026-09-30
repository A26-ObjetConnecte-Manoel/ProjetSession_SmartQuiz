#pragma once
#include <Arduino.h>

class SensorData
{
private:
    String source;
    String type;
    float value;
    String unit;
    unsigned long timestamp;

public:
    SensorData();

    SensorData(
        String source,
        String type,
        float value,
        String unit,
        unsigned long timestamp);

    String getSource() const;
    String getType() const;
    float getValue() const;
    String getUnit() const;
    unsigned long getTimestamp() const;
};
