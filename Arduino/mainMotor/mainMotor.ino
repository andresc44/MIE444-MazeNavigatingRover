//MIE444 Maze Navigating Rover 2022 Fall Semester-Motor Arduino
//Authors: Andres Cervera Rozo, Christopher Tong,
//         Liam Toner, Nathalie Cristofaro
//good reference link https://github.com/ros-drivers/rosserial/blob/noetic-devel/rosserial_arduino/src/ros_lib/tests/float64_test/float64_test.pde
#include <ros.h>
ros::NodeHandle nh; //initialize node handle object

//#include "Accessories.h"
//#include "BlockRetrieval.h"
#include "Pinout.h" // liam will modify pinout header to reflect electrnoics
#include "Direction.h"


//Constants as CONSTANT
//Functions as Function_Name
//Varaiables as variableName
//Class as Class

uint16_t tof = 0; 

void setup() {
  nh.initNode(); // initialize the Ros node handle
  Serial.begin(9600);
  DC_Motor_Setup();
  //Accessory_Setup();
  //Servo_Setup();
}

void loop() {
  nh.spinOnce(); // handles all ROS communication callbacks
  delay(1);//unsure if this controls frequency at which new data is published to the node
}
