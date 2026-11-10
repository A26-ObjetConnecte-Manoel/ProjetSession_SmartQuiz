#pragma once
#include <Arduino.h>
#include "../include/models/SensorData.h"

enum class CommandType
{
    START,
    RESET,
    CONFIG,
    INVALID
};

struct Command
{
    CommandType type = CommandType::INVALID;
    String name = "inconnu";
    unsigned long dureeMaxS = 0;
    String error = "";
};

class JsonService
{

public:
    String toJson(const SensorData data, String stateName);
    static String buildResult(int round, int winner);
    static String buildAck(const String &name, const String &statut, const String &message);
    static Command parseCommand(const String &topic, const String &payload);
};