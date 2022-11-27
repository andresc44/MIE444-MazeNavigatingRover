#include "Adafruit_VL53L0X.h"
#include <Servo.h>
#include "RunningAverage.h"

const uint16_t THRESHOLD = 110;
long time_ref;
int16_t servo_angle = 180;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;
RunningAverage myRA(10);
Servo myservo;  // create servo object to control a servo



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test.");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  
  // power
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  // start continuous ranging
  myservo.attach(6);
  myservo.write(servo_angle);
  myRA.clear();
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  uint16_t distance = measure.RangeMilliMeter;
  myRA.addValue(distance);

  if (myRA.getAverage() < THRESHOLD){
    servo_angle = 0;
  }
  myservo.write(servo_angle);
  
}
