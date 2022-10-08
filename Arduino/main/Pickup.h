#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
void TOF_Setup() {
  while (! Serial) {
    delay(1);
  }
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // start continuous ranging
  lox.startRangeContinuous();
}

uint16_t TOF_Heartbeat() {
  if (lox.isRangeComplete()) {
    return lox.readRange();
  }
  else {
    return 0;
  }
}
