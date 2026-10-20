#include <Arduino.h>
#include <Wire.h>

#include "../include/config/Config.h"
#include "../include/core/Application.h"
#include "../include/input/boutonInput.h"
#include "../include/output/SerialOutput.h"

Application app;

SerialOutput serialOutput;

Bouton bouton1(BOUTONJ1, "Joueur1");
Bouton bouton2(BOUTONJ2, "Joueur2");

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