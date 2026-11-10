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

    String pendingTopic;
    String pendingPayload;
    bool messagePending = false;

    void onMessage(char *topic, byte *payload, unsigned int length);

public:
    MqttService(WifiService &wifi, const char *broker, uint16_t port,
                const char *clientId, const char *username, const char *password);

    void begin();
    void update();
    bool publish(const char *topic, const String payload);
    bool isConnected();
    bool hasMessage() const;
    String getMessageTopic() const;
    String getMessagePayload() const;
    void clearMessage();
};