#include "../include/models/SensorData.h"

SensorData::SensorData()
    : source(""), type(""), value(0), unit(""), timestamp(0)
{
}

SensorData::SensorData(
    String source,
    String type,
    float value,
    String unit,
    unsigned long timestamp)
    : source(source), type(type), value(value), unit(unit), timestamp(timestamp)
{
}

String SensorData::getSource() const
{
    return source;
}

String SensorData::getType() const
{
    return type;
}

float SensorData::getValue() const
{
    return value;
}

String SensorData::getUnit() const
{
    return unit;
}

unsigned long SensorData::getTimestamp() const
{
    return timestamp;
}
