int sw_state_1 = 0;
int sw_state_2 = 0;

void DIP_Setup() {
  pinMode(DIPPin1, INPUT_PULLUP);
  pinMode(DIPPin2, INPUT_PULLUP);
}

uint8_t DIP_Heartbeat() {
  sw_state_1 = digitalRead(sw_pin_1);
  sw_state_2 = digitalRead(sw_pin_2);
    
  if      (sw_state_1 == LOW && sw_state_2 == LOW)   return 0;
  else if (sw_state_1 == LOW && sw_state_2 == HIGH)  return 1;
  else if (sw_state_1 == HIGH && sw_state_2 == LOW)  return 2;
  else    (sw_state_1 == HIGH && sw_state_2 == HIGH) return 3;
}
