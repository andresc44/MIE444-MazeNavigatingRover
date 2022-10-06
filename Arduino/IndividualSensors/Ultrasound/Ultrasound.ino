int trigPin= 9;
int echoPin = 10;
float speedSoundcm = 0.034; //units of cm/us

void setup() {
  // put your setup code here, to run once:
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float pingTime = pulseIn (echoPin, HIGH); //unit us
  float dist = pingTime * speedSoundcm * 0.5; //unit cm
  
  Serial.print("\npingTime: ");
  Serial.print(pingTime);
  Serial.println(" us");
  Serial.print("distance: ");
  Serial.print(dist);
  Serial.println(" cm");
  delay(500);

}
