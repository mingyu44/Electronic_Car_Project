#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Set PinNumber
int Trig = 13;
int Ehco = 12;
int Buzer = 8;
int LedGreen = 7;
int LedYellow = 6;
int LedRed = 5;

unsigned long duration;
float distance;

//Set LCD ID&Size
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  //Set PinMode
  pinMode(Trig, OUTPUT);
  pinMode(Ehco, INPUT);
  pinMode(Buzer, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(LedYellow, OUTPUT);
  pinMode(LedRed, OUTPUT);

  //Set LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  //Work Distance Sensor
  digitalWrite(Trig, LOW);
  digitalWrite(Ehco, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  //Calculate Distance
  duration = pulseIn(Ehco, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;

  //Output Distance in Serial Window
  Serial.print(distance / 100);
  Serial.println("m");

  //Output Distance in LCD
  lcd.setCursor(0, 1);
  lcd.print(distance / 100);
  lcd.println(" m               ");
  
  if(distance <= 20) {
     lcd.setCursor(0, 0);
     lcd.print("    Crushed!!    ");
     digitalWrite(LedRed, HIGH);
     digitalWrite(LedYellow, LOW);
     digitalWrite(LedGreen, LOW);
     //Output Buzer
     for (int i = 0; i < 5; i++) { 
        tone (Buzer, 440, 200); 
        delay (300); 
     }
  }
  
  else if(distance <= 75) {
     lcd.setCursor(0, 0);
     lcd.print("    Warning!!    ");
     digitalWrite(LedRed, LOW);
     digitalWrite(LedYellow, HIGH);
     digitalWrite(LedGreen, LOW);
     digitalWrite(Buzer, LOW);
  }
  
  else {
     lcd.setCursor(0, 0);
     lcd.print("      Safe       ");
     digitalWrite(LedRed, LOW);
     digitalWrite(LedYellow, LOW);
     digitalWrite(LedGreen, HIGH);
     digitalWrite(Buzer, LOW);
  }

  delay(65);
}
