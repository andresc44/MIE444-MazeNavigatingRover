byte payload[19];
uint8_t input[10];
// https://www.arduino.cc/reference/en/language/functions/communication/serial/

struct RaspberryPiMessage {
    uint8_t motorsArray[6] = {0, 0, 0, 0, 0, 0};
    uint8_t servoAngle = 0;
    bool feedbackArray[2] = {0, 0};
};
RaspberryPiMessage piMsg;

bool Receive_From_Pi() {
  for (uint8_t i = 0; i < 10; i++) {
    input[i] = Serial.read();
  }
  if (input[0] == 13 && input[9] == 14){
    piMsg.motorsArray[0] = input[1];
    piMsg.motorsArray[1] = input[2];
    piMsg.motorsArray[2] = input[3];
    piMsg.motorsArray[3] = input[4];
    piMsg.motorsArray[4] = input[5];
    
    piMsg.servoAngle = input[6];

    piMsg.feedbackArray[0] = input[7];
    piMsg.feedbackArray[0] = input[8];
    return true;
  }
  else {
    Serial.println(F("Error in reading Pi data"));
    return false;
  }
}

void Send_To_Pi(uint16_t ultra[], bool ir[], uint16_t tof, uint8_t dip){
  payload[0] = 0x11;
  payload[1] = highByte(ultra[0]);
  payload[2] = lowByte(ultra[0]);
  payload[3] = highByte(ultra[1]);
  payload[4] = lowByte(ultra[1]);
  payload[5] = highByte(ultra[2]);
  payload[6] = lowByte(ultra[2]);
  payload[7] = highByte(ultra[3]);
  payload[8] = lowByte(ultra[3]);
  payload[9] = highByte(ultra[4]);
  payload[10] = lowByte(ultra[4]);

  payload[11] = byte(ir[0]);
  payload[12] = byte(ir[1]);
  payload[13] = byte(ir[2]);
  payload[14] = byte(ir[3]);
  
  payload[15] = highByte(tof);
  payload[16] = lowByte(tof);
  payload[17] = byte(dip);
  payload[18] = 0x22;
  Serial.write(payload, 19);
}
