#include "../include/config/Config.h"
#include "../include/services/DisplayService.h"
#include "../include/assets/Icon.h"

DisplayService::DisplayService(Adafruit_SSD1306 &display)
    : display(display),
      ready(false)
{
}

void DisplayService::begin()
{
    ready = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

    if (!ready)
    {
        Serial.println("[OLED] Ecran introuvable - le systeme continue sans affichage");
        return;
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.display();
    Serial.println("[OLED] Pret");
}

bool DisplayService::isReady() const
{
    return ready;
}

void DisplayService::showMessage(const String &line1, const String &line2)
{
    if (!ready)
        return;

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(line1);
    display.println(line2);
    display.display();
}

void DisplayService::drawHeader(int round)
{
    display.setTextSize(1);
    display.setCursor(0, 3);
    display.print("SmartQuiz");

    // Aligné à droite : 6 pixels par caractère en taille 1
    String manche = "Manche " + String(round);
    display.setCursor(SCREEN_WIDTH - manche.length() * 6, 3);
    display.print(manche);

    display.drawFastHLine(0, 13, SCREEN_WIDTH, SSD1306_WHITE);
}

void DisplayService::showGameState(QuizState state, int round, int winner, unsigned long remainingMs)
{
    if (!ready)
        return;

    // Valeurs par défaut : état ERREUR
    const uint8_t *icon = ICON_ERREUR;
    String title = "ERREUR";
    String big = "!";
    String hint = "r = reprendre";

    // Note : la police de base ne gère pas les accents
    switch (state)
    {
    case QuizState::ATTENTE:
        icon = ICON_ATTENTE;
        title = "EN ATTENTE";
        big = "PRET";
        hint = "s = demarrer";
        break;

    case QuizState::MANCHE:
        icon = ICON_MANCHE;
        title = "A VOS BUZZERS!";
        big = String((remainingMs + 999) / 1000) + " s"; // arrondi vers le haut
        hint = "Le premier gagne";
        break;

    case QuizState::GAGNANT:
        icon = ICON_GAGNANT;
        title = "GAGNANT";
        big = "J" + String(winner);
        hint = "r = reinitialiser";
        break;

    case QuizState::REINITIALISATION:
        icon = ICON_REINITIALISATION;
        title = "Remise a zero";
        big = "...";
        hint = "Patientez";
        break;

    case QuizState::ERREUR:
        break; // valeurs par défaut
    }

    display.clearDisplay();
    drawHeader(round);

    display.drawBitmap(4, 22, icon, ICON_SIZE, ICON_SIZE, SSD1306_WHITE);

    display.setTextSize(1);
    display.setCursor(36, 20);
    display.print(title);

    display.setTextSize(2);
    display.setCursor(36, 32);
    display.print(big);

    display.setTextSize(1);
    display.setCursor(0, 56);
    display.print(hint);

    display.display();
}