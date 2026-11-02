#include "../include/services/MqttService.h"
#include "../include/config/Config.h"

MqttService::MqttService(WifiService &wifi, const char *broker, uint16_t port,
                         const char *clientId, const char *username, const char *password)
    : wifi(wifi), client(wifiClient), broker(broker), port(port),
      clientId(clientId), username(username), password(password)
{
}

void MqttService::begin()
{
    client.setServer(broker, port);
    client.setSocketTimeout(2);
    client.setBufferSize(512);
}

void MqttService::update()
{
    bool connected = client.connected();

    if (connected && !wasConnected)
    {
        Serial.println("[MQTT] Connecte au broker");
    }
    else if (!connected && wasConnected)
    {
        Serial.println("[MQTT] Connexion perdue");
    }
    wasConnected = connected;

    if (connected)
    {
        client.loop();
        return;
    }

    if (!wifi.isconnected())
        return;

    if (millis() - lastAttemptMs >= MQTT_RETRY_INTERVAL_MS)
    {
        lastAttemptMs = millis();

        if (!client.connect(clientId, username, password))
        {
            Serial.printf("[MQTT] Echec, state = %d\n", client.state());
        }
    }
}

bool MqttService::publish(const char *topic, const String payload)
{
    if (!client.connected())
        return false;
    return client.publish(topic, payload.c_str());
}

bool MqttService::isConnected()
{
    return client.connected();
}