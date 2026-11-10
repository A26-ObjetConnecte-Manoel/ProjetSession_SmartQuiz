#include "../include/services/JsonService.h"
#include <ArduinoJson.h>
#include "config/Config.h"

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
// Résultat d'une manche (topic data)
String JsonService::buildResult(int round, int winner)
{
    JsonDocument doc;
    doc["manche"] = round;
    doc["joueur"] = winner;
    doc["timestamp"] = millis();

    String json;
    serializeJson(doc, json);
    return json;
}

// Confirmation d'une commande (topic ack)
String JsonService::buildAck(const String &name, const String &statut, const String &message)
{
    JsonDocument doc;
    doc["recu"] = name;
    doc["statut"] = statut;
    doc["message"] = message;
    doc["timestamp"] = millis();

    String json;
    serializeJson(doc, json);
    return json;
}

// Lecture et validation d'une commande reçue
Command JsonService::parseCommand(const String &topic, const String &payload)
{
    Command command;
    JsonDocument doc;

    if (deserializeJson(doc, payload))
    {
        command.error = "JSON invalide";
        return command;
    }

    if (topic == TOPIC_CMD)
    {
        if (!doc["cmd"].is<const char *>())
        {
            command.error = "champ cmd manquant";
            return command;
        }
        command.name = doc["cmd"].as<const char *>();

        if (command.name == "start")
            command.type = CommandType::START;
        else if (command.name == "reset")
            command.type = CommandType::RESET;
        else
            command.error = "commande inconnue";
        return command;
    }

    if (topic == TOPIC_CONFIG)
    {
        command.name = "config";

        if (!doc["dureeMaxS"].is<int>())
        {
            command.error = "champ dureeMaxS manquant ou non entier";
            return command;
        }
        int duree = doc["dureeMaxS"].as<int>();
        if (duree < DUREE_MIN_S || duree > DUREE_MAX_S)
        {
            command.error = "dureeMaxS hors limites";
            return command;
        }
        command.type = CommandType::CONFIG;
        command.dureeMaxS = duree;
        return command;
    }

    command.error = "topic inconnu";
    return command;
}