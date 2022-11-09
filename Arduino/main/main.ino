//MIE444 Maze Navigating Rover 2022 Fall Semester
//Authors: Andres Cervera Rozo, Christopher Tong,
//         Liam Toner, Nathalie Cristofaro
// chris was here
#include "Pinout.h" // liam will modify pinout header to reflect electrnoics
#include "Accessories.h"
#include "Direction.h"
#include "Communications.h"
#include "Localization.h"
#include "ObstacleAvoidance.h"
#include "BlockRetrieval.h"

//Constants as CONSTANT
//Functions as Function_Name
//Varaiables as variableName
//Class as Class

// this main file was wrritten as while ago so needs to be restructured
// this main file is specifically for motor driver arduino
// a seperate main file will need to be created


uint16_t tof = 0; 

void setup() {
  Serial.begin(9600);
  //TOF_Setup();
  //IR_Setup();
  //Accessory_Setup();
  DC_Motor_Setup();
  //Servo_Setup();
}

void loop() {
  //outputs
  if (Receive_From_Pi()){
    Move_Robot(piMsg.motorsArray);
    //Move_Servo(piMsg.servoAngle);
    Feedback(piMsg.feedbackArray); // look for it in another header
  }
  
  //inputs
  //tof = TOF_Heartbeat();
  //Ultrasonic_Heartbeat();
  //IR_Heartbeat();
  //dip = DIP_Heartbeat();
  //Send_To_Pi(ultra.array, ir.array, tof, dip);
}
