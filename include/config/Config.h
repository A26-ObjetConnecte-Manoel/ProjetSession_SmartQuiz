#pragma once

#define BOUTONJ1 35
#define BOUTONJ2 36
#define SERIAL_BAUD_RATE 115200
#define DEBOUNCE_DELAY 50

#define TIME_MAX_GAME_MS 15000
#define REINIT_DURATION_MS 1000
#define DIAGNOSTIC_INTERVAL_MS 10000
#define STATE_REFRESH_MS 1000

#define NOM_J1 "Joueur 1"
#define NOM_J2 "Joueur 2"

#define LED_J1_PIN 25
#define LED_J2_PIN 26
#define BUZZER_PIN 17

#define BIP_COURT_MS 80
#define BIP_VICTOIRE_MS 400
#define BUZZER_FREQ_HZ 2000

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

#define TYPE_BOUTON "bouton"
#define TYPE_ETAT "etat"

#define WIFI_RECONNECT_INTERVAL_MS 5000
#define WIFI_SSID "EcoleDuWeb2.4g"
#define WIFI_PASSWORD "EcoleDuWEB@@"

#define MQTT_HOST "mqtt.manoelt.lab.edwrdl.ca"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "smartQuizStation01"
#define MQTT_TOPIC "smartQuiz/station01/observations"
#define MQTT_RETRY_INTERVAL_MS 5000
#define MQTT_USERNAME "manoel"
#define MQTT_PASSWORD "Manoel2003"