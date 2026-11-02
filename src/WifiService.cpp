#include "../include/services/WifiService.h"
#include "../include/config/Config.h"
#include <WiFi.h>

WifiService::WifiService(const char *ssid, const char *password)
    : ssid(ssid), password(password)
{
}
void WifiService::begin()
{
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(false);
    WiFi.begin(ssid, password);
    lastAttemptMs = millis();
}
void WifiService::update()
{
    if (WiFi.status() != WL_CONNECTED && millis() - lastAttemptMs >= WIFI_RECONNECT_INTERVAL_MS)
    {
        WiFi.reconnect();
        lastAttemptMs = millis();
    }
}

bool WifiService::isconnected() const
{
    return WiFi.status() == WL_CONNECTED;
}