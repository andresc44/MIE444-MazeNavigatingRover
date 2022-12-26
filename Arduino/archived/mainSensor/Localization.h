struct IRArray {
    bool array[4];
};
IRArray ir;

void IR_Setup() {
  pinMode (IRPIN1, INPUT);
  pinMode (IRPIN2, INPUT);
  pinMode (IRPIN3, INPUT);
  pinMode (IRPIN4, INPUT);
  Serial.println(F("IR Sensors Ready"));
}

IRArray IR_Heartbeat() {
  ir.array[0] = digitalRead (IRPIN1);
  ir.array[1] = digitalRead (IRPIN2);
  ir.array[2] = digitalRead (IRPIN3);
  ir.array[3] = digitalRead (IRPIN4);
}
