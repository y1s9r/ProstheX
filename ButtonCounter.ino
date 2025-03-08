#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,  16, 2);


int buttonPin = 2;
int repeatCheck;
int counter = 0;
int buttonReading;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Score:");
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonReading = digitalRead(buttonPin);
  if (buttonReading != repeatCheck)
  {
    if (buttonReading == LOW)
    {
      counter++;
      lcd.setCursor(0, 1);
      lcd.print(counter);
    }
    delay(50);
  }
  repeatCheck = buttonReading;
}
