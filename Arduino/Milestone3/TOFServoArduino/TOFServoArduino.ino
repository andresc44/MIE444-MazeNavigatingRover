#include <ros.h>
#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

#include <std_msgs/UInt16.h> //to publish TOF data
#include <std_msgs/Bool.h> //to subscribe to servo commands

Servo servo;
const uint8_t servoPin = 6;

VL53L0X sensor;

ros::NodeHandle nh;
std_msgs::UInt16 TOF_msg;

ros::Publisher pub_TOF("TOF", &TOF_msg);

void messageCb(const std_msgs::Bool& scoop) {

  if(scoop.data){
    servo.write(0);
  }
  else
  servo.write(180);

  //TOF_msg.data = distance;
  //pub_TOF.publish(&TOF_msg);
  
}

//Instantiate publishers and subscribers we will be using
//Topic we will be subscibing to is called "LEDs"
//Callback function is called messageCb
ros::Subscriber<std_msgs::Bool> sub("servo", &messageCb );

void setup(){
  
  nh.initNode();
  nh.advertise(pub_TOF);
  nh.subscribe(sub);

  servo.attach(servoPin);
  servo.write(180);
  //Serial.begin(115200);

  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    //Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

    sensor.startContinuous();
  
}

void loop(){

  TOF_msg.data = sensor.readRangeContinuousMillimeters();
  pub_TOF.publish(&TOF_msg);
  nh.spinOnce();
  delay(100);

//  Serial.print(sensor.readRangeContinuousMillimeters());
//  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
//
//  Serial.println();
//  
}
