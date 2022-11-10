void Accessory_Setup() {
  pinMode(LIGHTPIN, OUTPUT);
  Serial.println(F("Light Ready"));
}

void Feedback(bool outputs[]) {
  digitalWrite(LIGHTPIN, outputs[0]);
  digitalWrite(SOUNDPIN, outputs[1]);
}
