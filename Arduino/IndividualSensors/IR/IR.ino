char pinIR = A1;
int exp5cmVal = 428; //value found from experimentation at 5cm away
void setup() {
  // put your setup code here, to run once:
 pinMode(pinIR, INPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int IRread = analogRead(pinIR);
  Serial.print("\nIRRead: ");
  Serial.println(IRread);
  float IRVoltage = float(IRread)/1023.0*5.0;
  Serial.print("IRVoltage: ");
  Serial.println(IRVoltage);

  bool Under5 = IRread > exp5cmVal;
  if (Under5) {
    Serial.println("Obstacle is 5cm away or less");
  }
  else {
    Serial.println("Obstacle is farther than 5cm away");
  }
  delay(500);
}
