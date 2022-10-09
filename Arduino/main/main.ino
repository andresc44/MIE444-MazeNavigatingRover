//MIE444 Maze Navigating Rover 2022 Fall Semester
//Authors: Andres Cervera Rozo, Christopher Tong,
//         Liam Toner, Nathalie Cristofaro

#include 'Pinout.h'
#include 'Accessories.h'
#include 'Direction.h'
#include 'Communications.h'
#include 'Localization.h'
#include 'ObstacleAvoidance.h'
#include 'BlockRetrieval.h'

//Constants as CONSTANT
//Functions as Function_Name
//Varaiables as variableName
//Class as Class

array uint16_t[9] piCommands = [0, 0, 0, 0, 0, 0, 0, 0, 0];

void setup() {
  Serial.begin(9600);
  TOF_Setup();
  Ultrasonic_Setup();
  IR_Setup();
  DIP_Setup();
  DC_Motor_Setup();
  Servo_Setup();
}

void loop() {
  //outputs
  
  piCommands = Receive_From_Pi();
  Move_Robot(piCommands[0:5]);
  Move_Servo(piCommands[6]);
  Feedback(piCommands[7:8];

  //inputs
  tof = TOF_Heartbeat();
  ultra = Ultrasonic_Heartbeat();
  ir = IR_Heartbeat();
  dip = DIP_Heartbeat();
  Send_To_Pi(ultra, ir, tof, dip);
}
