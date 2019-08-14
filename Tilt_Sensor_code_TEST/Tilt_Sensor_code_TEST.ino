int tilt = 2;

void setup()
{
  Serial.begin(9600);
  pinMode(tilt, INPUT);
}

void loop() {
  Serial.println(digitalRead(tilt));
  delay(1);  
}
