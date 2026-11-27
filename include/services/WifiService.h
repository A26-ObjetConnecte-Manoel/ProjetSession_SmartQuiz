#pragma once
#include <WiFi.h>
#include <WiFiManager.h>

class WifiService
{
public:
    void begin();
    void update();
    bool isconnected() const;

private:
    WiFiManager wm;
    unsigned long lastAttemptMs = 0;
    bool wasConnected = false;
};