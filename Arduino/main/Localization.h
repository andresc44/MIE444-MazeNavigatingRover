bool IR1 true
bool IR2 true
bool IR3 true
bool IR4 true

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
  IR.array[0] = digitalRead (IRSensor1);
  IR.array[1] = digitalRead (IRSensor2);
  IR.array[2] = digitalRead (IRSensor3);
  IR.array[3] = digitalRead (IRSensor4);
}
