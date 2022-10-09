const float SPEEDSOUND = 0.17; //units of mm/us, accounting for double trajectory
float pingTime1 = 0;
float pingTime2 = 0;
float pingTime3 = 0;
float pingTime4 = 0;
float pingTime5 = 0;

struct UltraArray {
    uint16_t array[5];
};

void Ultrasonic_Setup() {
  pinMode(TRIGPIN1, OUTPUT);
  pinMode(ECHOPIN1, INPUT);
  pinMode(TRIGPIN2, OUTPUT);
  pinMode(ECHOPIN2, INPUT);
  pinMode(TRIGPIN3, OUTPUT);
  pinMode(ECHOPIN3, INPUT);
  pinMode(TRIGPIN4, OUTPUT);
  pinMode(ECHOPIN4, INPUT);
  pinMode(TRIGPIN5, OUTPUT);
  pinMode(ECHOPIN5, INPUT);
}

UltraArray Ultrasonic_Heartbeat() {
  UltraArray ultra;
  
  digitalWrite(TRIGPIN1, LOW);
  digitalWrite(TRIGPIN2, LOW);
  digitalWrite(TRIGPIN3, LOW);
  digitalWrite(TRIGPIN4, LOW);
  digitalWrite(TRIGPIN5, LOW);
  
  delayMicroseconds(2000);
  
  digitalWrite(TRIGPIN1, HIGH);
  digitalWrite(TRIGPIN2, HIGH);
  digitalWrite(TRIGPIN3, HIGH);
  digitalWrite(TRIGPIN4, HIGH);
  digitalWrite(TRIGPIN5, HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(TRIGPIN1, LOW);
  digitalWrite(TRIGPIN2, LOW);
  digitalWrite(TRIGPIN3, LOW);
  digitalWrite(TRIGPIN4, LOW);
  digitalWrite(TRIGPIN5, LOW);
  
  pingTime1 = pulseIn (ECHOPIN1, HIGH); //unit us
  pingTime2 = pulseIn (ECHOPIN2, HIGH); //unit us
  pingTime3 = pulseIn (ECHOPIN3, HIGH); //unit us
  pingTime4 = pulseIn (ECHOPIN4, HIGH); //unit us
  pingTime5 = pulseIn (ECHOPIN5, HIGH); //unit us

  ultra.array[0] = pingTime1 * SPEEDSOUND; //unit mm
  ultra.array[1] = pingTime2 * SPEEDSOUND; //unit mm
  ultra.array[2] = pingTime3 * SPEEDSOUND; //unit mm
  ultra.array[3] = pingTime4 * SPEEDSOUND; //unit mm
  ultra.array[4] = pingTime5 * SPEEDSOUND; //unit mm
  
  return ultra;
}
