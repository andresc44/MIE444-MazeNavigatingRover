//MIE444 Maze Navigating Rover 2022 Fall Semester-Motor Arduino
//Authors: Andres Cervera Rozo, Christopher Tong,
//         Liam Toner, Nathalie Cristofaro
//good reference link https://github.com/ros-drivers/rosserial/blob/noetic-devel/rosserial_arduino/src/ros_lib/tests/float64_test/float64_test.pde

#include <SoftwareSerial.h>
#define rxPin 12
#define txPin 13
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

#include <ros.h>
ros::NodeHandle nh; //initialize node handle object
#include "Pinout.h" // liam will modify pinout header to reflect electrnoics
#include "Direction.h"

//#include "Accessories.h"
//#include "BlockRetrieval.h"
//Constants as CONSTANT
//Functions as Function_Name
//Varaiables as variableName
//Class as Class


void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);
  mySerial.println("Software Serial Started");
  nh.initNode(); // initialize the Ros node handle
  nh.subscribe(sub); //subscribe node nh to topic wheelsPWM
//  nh.advertise(pub);
  Serial.begin(9600);
  DC_Motor_Setup();
  //Accessory_Setup();
  //Servo_Setup();
  //nh.loginfo("Done setup\n");
//  mySerial.println("Motor Setup Started");
}

void loop() {
  mySerial.println("Loop start");
  nh.spinOnce(); // handles all ROS communication callbacks
  delay(1);//unsure if this controls frequency at which new data is published to the node
}
