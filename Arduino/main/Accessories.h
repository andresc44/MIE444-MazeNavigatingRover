bool swState1 = false;
bool swState2 = false;

void DIP_Setup() {
  pinMode(DIPPIN1, INPUT_PULLUP);
  pinMode(DIPPIN2, INPUT_PULLUP);
  pinMode(LIGHTPIN, OUTPUT);
  pinMode(SOUNDPIN, OUTPUT);
}

uint8_t DIPHeartbeat() {
  sw_state_1 = digitalRead(DIPPIN1);
  sw_state_2 = digitalRead(DIPPIN2);
    
  if      (!swState1 && !swState2)  return 0;
  else if (!swState1 &&  swState2)  return 1;
  else if ( swState1 && !swState2)  return 2;
  else if ( swState1 &&  swState2)  return 3;
  else                              return 4;
}

void Feedback(array bool outputs) {
  digitalWrite(LIGHTPIN, outputs[0]);
  digitalWrite(SOUNDPIN, outputs[1]);
}
