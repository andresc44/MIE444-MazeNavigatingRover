//direction the robot will go in relative to car body
#include <std_msgs/Int16MultiArray.h> // pwm data is sent as 16 bit array


std_msgs::Int16MultiArray msg;
ros::Publisher pub("/results", &msg);


void messageCb(const std_msgs::Int16MultiArray& pwm_msg) {
  mySerial.println("inside callback");
  mySerial.print("Software Serial Started, Payload: [");
  mySerial.print(pwm_msg.data[0]);
  mySerial.print(", ");
  mySerial.print(pwm_msg.data[1]);
  mySerial.print(", ");
  mySerial.print(pwm_msg.data[2]);
  mySerial.print(", ");
  mySerial.print(pwm_msg.data[3]);
  mySerial.print(", ");
  mySerial.print(pwm_msg.data[4]);
  mySerial.print(", ");
  mySerial.print(pwm_msg.data[5]);
  mySerial.println("]");

 //input 1 is HIGH-> clockwise
 //input 2 is LOW -> clockwise
// msg.data[0] = pwm_msg.data[0];
// msg.data[1] = pwm_msg.data[1];
// msg.data[2] = pwm_msg.data[2];
// msg.data[3] = pwm_msg.data[3];
// msg.data[4] = pwm_msg.data[4];
// msg.data[5] = pwm_msg.data[5];
// msg.data_length = 6;
//
// pub.publish(&msg);
  digitalWrite(DIR1A, HIGH);
  digitalWrite(DIR1B, LOW);
  digitalWrite(DIR2A, HIGH);
  digitalWrite(DIR2B, LOW);
  digitalWrite(DIR3A, HIGH);
  digitalWrite(DIR3B, LOW);

  analogWrite(EN1, pwm_msg.data[1]);
  analogWrite(EN2, pwm_msg.data[3]);
  analogWrite(EN3, pwm_msg.data[5]);
  //Adjust_PWM(pwm_msg); //Where Liam's code will go
}


ros::Subscriber<std_msgs::Int16MultiArray> sub("wheelsPWM", &messageCb );

void DC_Motor_Setup() {
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);

  pinMode(DIR1A, OUTPUT);
  pinMode(DIR1B, OUTPUT);
  pinMode(DIR2A, OUTPUT);
  pinMode(DIR2B, OUTPUT);
  pinMode(DIR3A, OUTPUT);
  pinMode(DIR3B, OUTPUT);
  pinMode(ENCODER1A, INPUT);
  pinMode(ENCODER1B, INPUT);
  pinMode(ENCODER2A, INPUT);
  pinMode(ENCODER2B, INPUT);
  pinMode(ENCODER3A, INPUT);
  pinMode(ENCODER3B, INPUT);
  
  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR1B, LOW);
  digitalWrite(DIR2A, LOW);
  digitalWrite(DIR2B, LOW);
  digitalWrite(DIR3A, LOW);
  digitalWrite(DIR3B, LOW);
  mySerial.println("Motors setup Ready");
}
