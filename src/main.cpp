#include <Arduino.h>
#include <Wire.h>

#include "../include/config/Config.h"
#include "../include/core/Application.h"
#include "../include/input/boutonInput.h"
#include "../include/output/SerialOutput.h"
#include "../include/services/QuizStateService.h"

QuizStateService stateService(TIME_MAX_GAME_MS);
Application app(DIAGNOSTIC_INTERVAL_MS, stateService);
SerialOutput serialOutput;

Bouton bouton1(BOUTONJ1, NOM_J1);
Bouton bouton2(BOUTONJ2, NOM_J2);

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);

  delay(1000);

  app.addInput(&bouton1);
  app.addInput(&bouton2);
  app.addOutput(&serialOutput);

  app.begin();

  Serial.println("SmartQuiz v0.3.0 - Machine a etats");
  Serial.println("Commandes : 's' = demarrer une manche, 'r' = reinitialiser");
}

void loop()
{
  app.update();
}