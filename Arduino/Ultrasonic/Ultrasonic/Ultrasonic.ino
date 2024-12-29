int trigPin = 12;
int echoPin = 8;
long duration;
int distance;
int POINTS = 64;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  

  float avgDistance = 0;
  for(int i = 0; i < 64; i++){
    avgDistance += measureDistance();
  }

  avgDistance = avgDistance / 64;

  Serial.println(avgDistance);

  delay(100);

  

}

int measureDistance(){
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;  

  return distance;
}
