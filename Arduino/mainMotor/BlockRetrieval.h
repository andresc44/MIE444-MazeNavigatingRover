#include "Adafruit_VL53L0X.h"
#include <Servo.h>

Servo myServo;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void TOF_Setup() {
  while (! Serial) {
    delay(1);
  }
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  lox.startRangeContinuous();
  Serial.println(F("TOF Ready"));
}

void Servo_Setup() {
  myServo.attach(SERVOPIN);
  Serial.println(F("Servo Ready"));
}

uint16_t TOF_Heartbeat() {
  if (lox.isRangeComplete()) {
    return lox.readRange();
  }
  else {
    return 0;
  }
}

void Move_Servo(uint8_t pos) {
  myServo.write(pos);
}
