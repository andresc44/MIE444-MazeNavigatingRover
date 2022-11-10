//direction the robot will go in relative to car body
#include <ros.h>
#include <std_msgs/Int8MultiArray.h> // pwm data is sent as 8 bit array

//Creating a Callback Function for Subscriber
//Input: standard message
//The type of message is Empty
// The message name is pwm_msg
//uint8_t pwm_array[3] = {0, 0, 0}; //initialize pwm array
//bool dir_CW_array[3] = {HIGH, HIGH, HIGH}; //initialize direction array

ros::Subscriber<std_msgs::Int8MultiArray> sub("wheelsPWM", &messageCb );

void DC_Motor_Setup() {
  nh.subscribe(sub); //subscribe node nh to topic wheelsPWM
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  
  //setting up L298N Pins, there are 3 Motor controllers in total
  // Each MC needs In1 and In2, thats what DIR1A and DIR1B represent
  pinMode(DIR1A, OUTPUT);
  pinMode(DIR1B, OUTPUT);
  pinMode(DIR2A, OUTPUT);
  pinMode(DIR2B, OUTPUT);
  pinMode(DIR3A, OUTPUT);
  pinMode(DIR3B, OUTPUT);
  pinMode(ENCODER1A, OUTPUT);
  pinMode(ENCODER1B, OUTPUT);
  pinMode(ENCODER2A, OUTPUT);
  pinMode(ENCODER2B, OUTPUT);
  pinMode(ENCODER3A, OUTPUT);
  pinMode(ENCODER3B, OUTPUT);
  
  //Setting In1 and In2 on L298N to OFF so that no motors turn on
  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR1B, LOW);
  digitalWrite(DIR2A, LOW);
  digitalWrite(DIR2B, LOW);
  digitalWrite(DIR3A, LOW);
  digitalWrite(DIR3B, LOW);
  Serial.println(F("Motors Ready"));
}


// Control feedback code
void Ajust_PWM (uint8_t pwm[]) {
  // LIAM Put in all the PID code here
  //can also accept rpms if preferred
  analogWrite(EN1, pwm[0]);
  analogWrite(EN2, pwm[1]);
  analogWrite(EN3, pwm[2]);
}

void messageCb(const std_msgs::Int8MultiArray& pwm_msg) {
  //every time call back gets called it listens to topic for new pwm_msg and updates the motor values
  //pwm_msg will be an integer between -255 and 255
  // negative int is counter clockwise, positive int is clockwise
  //when you index into something you have to use .data extension
  //pwm_array = {abs(pwm_msg.data[0]),abs(pwm_msg.data[1]),abs(pwm_msg.data[2])}; // stores pwm values for motor 1,2,3
  //dir_CW_array = {pwm_msg.data[0] >= 0, pwm_msg.data[1] >= 0, pwm_msg.data[2] >= 0};
  //pwm_msg.data = {sign1, pwm1, sign2, pwm2, sign3, pwm3};
   
 //input 1 is HIGH-> clockwise
 //input 2 is LOW -> clockwise
  digitalWrite(DIR1A, pwm_msg.data[0]);
  digitalWrite(DIR1B, !pwm_msg.data[0]);
  digitalWrite(DIR2A, pwm_msg.data[2]);
  digitalWrite(DIR2B, !pwm_msg.data[2]);
  digitalWrite(DIR3A, pwm_msg.data[3]);
  digitalWrite(DIR3B, !pwm_msg.data[3]);

  analogWrite(EN1, pwm_msg.data[1]);
  analogWrite(EN2, pwm_msg.data[2]);
  analogWrite(EN3, pwm_msg.data[3]);
  //Adjust_PWM(pwm_msg); //Where Liam's code will go
}
