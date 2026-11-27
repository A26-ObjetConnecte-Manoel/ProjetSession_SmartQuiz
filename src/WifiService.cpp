#include "../include/services/WifiService.h"
#include "../include/config/Config.h"
#include "../include/config/secret.h"

void WifiService::begin()
{

    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(false);
    wm.setConfigPortalBlocking(false);
    wm.setConfigPortalTimeout(WIFI_CONFIG_PORTAL_TIMEOUT_MS);

    if (wm.autoConnect(WIFI_AP_NAME, WIFI_AP_PASSWORD))
    {
        Serial.println("[WIFI] Connecte : " + WiFi.localIP().toString());
    }
    else
    {
        Serial.println("[WIFI] Portail de configuration ouvert : " WIFI_AP_NAME);
    }
    lastAttemptMs = millis();
    wasConnected = isconnected();
}

void WifiService::update()
{
    wm.process();

    bool connected = isconnected();
    if (connected && !wasConnected)
    {
        Serial.println("[WIFI] Connecte : " + WiFi.localIP().toString());
    }
    if (!connected && wasConnected)
    {
        Serial.println("[WIFI] Connexion perdue");
    }
    wasConnected = connected;

    if (!connected && !wm.getConfigPortalActive() &&
        millis() - lastAttemptMs >= WIFI_RECONNECT_INTERVAL_MS)
    {
        Serial.println("[WIFI] Tentative de reconnexion...");
        WiFi.reconnect();
        lastAttemptMs = millis();
    }
}

bool WifiService::isconnected() const
{
    return WiFi.status() == WL_CONNECTED;
}