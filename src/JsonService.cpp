#include "../include/services/JsonService.h"
#include <ArduinoJson.h>

String JsonService::toJson(const SensorData data, String stateName)
{
    JsonDocument doc;
    doc["source"] = data.getSource();
    doc["type"] = data.getType();
    doc["value"] = data.getValue();
    doc["unit"] = data.getUnit();
    doc["timestamp"] = data.getTimestamp();
    doc["state"] = stateName;

    String json;
    serializeJson(doc, json);
    return json;
}