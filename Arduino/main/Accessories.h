bool swState1 = false;
bool swState2 = false;

void Accessory_Setup() {
  pinMode(DIPPIN1, INPUT_PULLUP);
  pinMode(DIPPIN2, INPUT_PULLUP);
  pinMode(LIGHTPIN, OUTPUT);
  pinMode(SOUNDPIN, OUTPUT);
  Serial.println(F("DIP, Lights, and Buzzer Ready"));
}

uint8_t DIP_Heartbeat() {
  swState1 = digitalRead(DIPPIN1);
  swState2 = digitalRead(DIPPIN2);
    
  if      (!swState1 && !swState2)  return 0;
  else if (!swState1 &&  swState2)  return 1;
  else if ( swState1 && !swState2)  return 2;
  else if ( swState1 &&  swState2)  return 3;
  else                              return 4;
}

void Feedback(bool outputs[]) {
  digitalWrite(LIGHTPIN, outputs[0]);
  digitalWrite(SOUNDPIN, outputs[1]);
}
