#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int Trig = 13;
int Ehco = 12;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Ehco, INPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
  digitalWrite(Trig, LOW);
  digitalWrite(Ehco, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  unsigned long duration = pulseIn(Ehco, HIGH);
  float distance = ((float)(340 * duration) / 10000) / 2;

  Serial.print(distance);
  Serial.println("cm");
  
  if(distance <= 5)
  {
     lcd.setCursor(0, 0);
     lcd.print("    Crushed!!    ");
  }
  else if(distance <= 150)
  {
     lcd.setCursor(0, 0);
     lcd.print("    Warning!!    ");
  }
  else
  {
     lcd.setCursor(0, 0);
     lcd.print("      Safe       ");
  }
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.println(" cm              ");

  delay(100);
}
