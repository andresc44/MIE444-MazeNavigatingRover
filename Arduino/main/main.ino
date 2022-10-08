#include <Pinout.h>
#include <Accessories.h>
#include <Direction.h>
#include <Dropoff.h>
#include <LidarObstacleAvoidance.h>
#include <Localization.h>
#include <ObstacleAvoidance.h>
#include <Pickup.h>

//  Congrats, you can see this message!
//hello, this is code
void setup() {
  // put your setup code here, to run once:
  TOF_Setup();
  Ultrasonic_Setup();
  IR_setup();
  DIP_Setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  TOF = TOF_heartbeat();
  ultra = Ultrasonic_Heartbeat();
  IR = IR_Heartbeat();
  DIP = DIP_Heartbeat();
  
  

}
