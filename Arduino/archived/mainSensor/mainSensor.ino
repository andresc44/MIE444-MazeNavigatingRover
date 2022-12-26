//MIE444 Maze Navigating Rover 2022 Fall Semester-Sensor Arduino
//Authors: Andres Cervera Rozo, Christopher Tong,
//         Liam Toner, Nathalie Cristofaro
//good reference link https://github.com/ros-drivers/rosserial/blob/noetic-devel/rosserial_arduino/src/ros_lib/tests/float64_test/float64_test.pde

#include "BlockRetrieval.h"
#include "Localization.h"
#include "ObstacleAvoidance.h"
#include "Pinout.h" // liam will modify pinout header to reflect electrnoics

//Constants as CONSTANT
//Functions as Function_Name
//Varaiables as variableName
//Class as Class

uint16_t tof = 0; 
ros::NodeHandle nh; //initialize node handle object

void setup() {
  nh.initNode(); // initialize the Ros node handle
  Serial.begin(9600);
  //TOF_Setup();
  //IR_Setup();
  //Ultrasonic_Setup()
}

void loop() {
  //tof = TOF_Heartbeat();
  //Ultrasonic_Heartbeat();
  //IR_Heartbeat();
  delay(1);
}
