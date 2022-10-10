//MIE444 Maze Navigating Rover 2022 Fall Semester
//Authors: Andres Cervera Rozo, Christopher Tong,
//         Liam Toner, Nathalie Cristofaro

#include "Pinout.h"
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

uint16_t piCommands[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t dip = 0;
uint16_t tof = 0;

void setup() {
  Serial.begin(9600);
  TOF_Setup();
  Ultrasonic_Setup();
  IR_Setup();
  Accessory_Setup();
  DC_Motor_Setup();
  Servo_Setup();
}

void loop() {
  //outputs
  if (Receive_From_Pi()){
    Move_Robot(piMsg.motorsArray);
    Move_Servo(piMsg.servoAngle);
    Feedback(piMsg.feedbackArray);
  }
  
  //inputs
  tof = TOF_Heartbeat();
  Ultrasonic_Heartbeat();
  IR_Heartbeat();
  dip = DIP_Heartbeat();
  Send_To_Pi(ultra.array, ir.array, tof, dip);
}
