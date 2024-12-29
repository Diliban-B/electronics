int infraredPin = 8;
void setup() {
  Serial.begin(9600);
  pinMode(infraredPin, INPUT);

}

void loop() {
  int sensorOut = digitalRead(infraredPin);
  Serial.println(sensorOut);

  delay(100);
}
