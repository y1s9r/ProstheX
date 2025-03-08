#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int NUM_LEDS = 5;
const int LED_PINS[NUM_LEDS] = {2, 3, 4, 5, 6};
const int BUTTON_PINS[NUM_LEDS] = {7, 8, 9, 10, 11};
const int GLOW_DURATION = 1000; // 1 second
const int GAME_DURATION = 30000; // 30 seconds

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

int score = 0;
int currentLED = -1;
unsigned long lastChangeTime = 0;
unsigned long gameStartTime = 0;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  
  lcd.init();
  lcd.backlight();
  lcd.print("Score: 0");
  
  randomSeed(analogRead(0));
  gameStartTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - gameStartTime >= GAME_DURATION) {
    endGame();
    return;
  }
  
  if (currentTime - lastChangeTime >= GLOW_DURATION || currentLED == -1) {
    changeLED();
  }
  
  checkButtons();
  
  updateLCD();
}

void changeLED() {
  if (currentLED != -1) {
    digitalWrite(LED_PINS[currentLED], LOW);
  }
  currentLED = random(NUM_LEDS);
  digitalWrite(LED_PINS[currentLED], HIGH);
  lastChangeTime = millis();
}

void checkButtons() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (digitalRead(BUTTON_PINS[i]) == HIGH) {
      if (i == currentLED) {
        score++;
        changeLED();
      }
      delay(50); // Simple debounce
    }
  }
}

void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Score: ");
  lcd.print(score);
  
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print((GAME_DURATION - (millis() - gameStartTime)) / 1000);
  lcd.print("s   ");
}

void endGame() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  
  lcd.clear();
  lcd.print("Game Over!");
  lcd.setCursor(0, 1);
  lcd.print("Final Score: ");
  lcd.print(score);
  
  while(true); // Stop the game
}
