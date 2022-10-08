const float speedSoundcm = 0.034; //units of cm/us
float pingTime1 = 0;
float pingTime2 = 0;
float pingTime3 = 0;
float pingTime4 = 0;
float pingTime5 = 0;

struct UltraArray {
    uint16_t array[5];
};

void Ultrasonic_Setup() {
  pinMode(TrigPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(TrigPin3, OUTPUT);
  pinMode(EchoPin3, INPUT);
  pinMode(TrigPin4, OUTPUT);
  pinMode(EchoPin4, INPUT);
  pinMode(TrigPin5, OUTPUT);
  pinMode(EchoPin5, INPUT);
}

UltraArray Ultrasonic_Heartbeat() {
  UltraArray ultra;
  
  digitalWrite(TrigPin1, LOW);
  digitalWrite(TrigPin2, LOW);
  digitalWrite(TrigPin3, LOW);
  digitalWrite(TrigPin4, LOW);
  digitalWrite(TrigPin5, LOW);
  
  delayMicroseconds(2000);
  digitalWrite(TrigPin1, HIGH);
  digitalWrite(TrigPin2, HIGH);
  digitalWrite(TrigPin3, HIGH);
  digitalWrite(TrigPin4, HIGH);
  digitalWrite(TrigPin5, HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(TrigPin1, LOW);
  digitalWrite(TrigPin2, LOW);
  digitalWrite(TrigPin3, LOW);
  digitalWrite(TrigPin4, LOW);
  digitalWrite(TrigPin5, LOW);
  
  pingTime1 = pulseIn (EchoPin1, HIGH); //unit us
  pingTime2 = pulseIn (EchoPin2, HIGH); //unit us
  pingTime3 = pulseIn (EchoPin3, HIGH); //unit us
  pingTime4 = pulseIn (EchoPin4, HIGH); //unit us
  pingTime5 = pulseIn (EchoPin5, HIGH); //unit us

  ultra.array[0] = 50 * pingTime1 * speedSoundcm; //unit mm
  ultra.array[1] = 50 * pingTime2 * speedSoundcm; //unit mm
  ultra.array[2] = 50 * pingTime3 * speedSoundcm; //unit mm
  ultra.array[3] = 50 * pingTime4 * speedSoundcm; //unit mm
  ultra.array[4] = 50 * pingTime5 * speedSoundcm; //unit mm
  
  return ultra;
}
