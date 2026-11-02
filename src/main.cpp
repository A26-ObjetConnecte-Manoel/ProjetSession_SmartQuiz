#include <Arduino.h>
#include <Wire.h>

#include "../include/config/Config.h"
#include "../include/core/Application.h"
#include "../include/input/boutonInput.h"
#include "../include/outputs/SerialOutput.h"
#include "../include/services/QuizStateService.h"
#include "../include/tasks/BuzzerTask.h"
#include "../include/tasks/WinnerLedTask.h"
#include "../include/services/DisplayService.h"
#include "../include/outputs/OledOutput.h"
#include "../include/services/WifiService.h"
#include "../include/services/MqttService.h"
#include "../include/outputs/MqttOutput.h"
#include "../include/services/JsonService.h"

QuizStateService stateService(TIME_MAX_GAME_MS);
Application app(DIAGNOSTIC_INTERVAL_MS, stateService);

Bouton bouton1(BOUTONJ1, NOM_J1);
Bouton bouton2(BOUTONJ2, NOM_J2);

SerialOutput serialOutput;
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DisplayService displayService(oled);
OledOutput oledOutput(displayService, stateService);
WifiService wifiService(WIFI_SSID, WIFI_PASSWORD);
MqttService mqttService(wifiService, MQTT_HOST, MQTT_PORT, MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);

MqttOutput mqttOutput(mqttService, stateService, MQTT_TOPIC);

BuzzerTask buzzerTask(BUZZER_PIN, stateService);
WinnerLedTask winnerLedTask1(LED_J1_PIN, 1, stateService);
WinnerLedTask winnerLedTask2(LED_J2_PIN, 2, stateService);

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);

  delay(1000);

  wifiService.begin();

  app.addInput(&bouton1);
  app.addInput(&bouton2);

  app.addOutput(&serialOutput);
  app.addOutput(&oledOutput);
  app.addOutput(&mqttOutput);

  app.begin();
  buzzerTask.begin();
  winnerLedTask1.begin();
  winnerLedTask2.begin();
  wifiService.begin();
  mqttService.begin();

  Serial.println("SmartQuiz v0.3.0 - Machine a etats");
  Serial.println("Commandes : 's' = demarrer une manche, 'r' = reinitialiser");
}

void loop()
{
  app.update();
  buzzerTask.update();
  winnerLedTask1.update();
  winnerLedTask2.update();
  mqttService.update();
  wifiService.update();
}