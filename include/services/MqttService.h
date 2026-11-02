#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "WifiService.h"

class MqttService
{
private:
    WifiService &wifi;
    WiFiClient wifiClient;
    PubSubClient client;

    const char *broker;
    uint16_t port;
    const char *clientId;

    const char *username;
    const char *password;

    unsigned long lastAttemptMs = 0;
    bool wasConnected = false;

public:
    MqttService(WifiService &wifi, const char *broker, uint16_t port,
                const char *clientId, const char *username, const char *password);

    void begin();
    void update();
    bool publish(const char *topic, const String payload);
    bool isConnected();
};