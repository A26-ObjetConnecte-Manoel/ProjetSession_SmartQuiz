#pragma once
#include <Arduino.h>

class WifiService
{
private:
    const char *ssid;
    const char *password;
    unsigned long lastAttemptMs = 0;
    bool wasConnected = false;

public:
    WifiService(const char *ssid, const char *password);

    void begin();
    void update();
    bool isconnected() const;
};