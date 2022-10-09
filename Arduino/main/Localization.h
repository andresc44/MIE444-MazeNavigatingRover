struct IRArray {
    bool array[4];
};

void IR_setup() {
  pinMode (IRSensor1, INPUT);
  pinMode (IRSensor2, INPUT);
  pinMode (IRSensor3, INPUT);
  pinMode (IRSensor4, INPUT);
}

IRArray IR_Heartbeat() {
  IRArray IR;
  IR.array[0] = digitalRead (IRPIN1);
  IR.array[1] = digitalRead (IRPIN1);
  IR.array[2] = digitalRead (IRPIN1);
  IR.array[3] = digitalRead (IRPIN1);
}
