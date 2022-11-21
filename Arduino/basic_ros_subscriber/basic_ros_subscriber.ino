#include <ros.h>
#include <std_msgs/Empty.h>
#include <SoftwareSerial.h>
#include <std_msgs/Int16MultiArray.h> // pwm data is sent as 16 bit array
//#include <std_msgs/Int16.h> // pwm data is sent as 16 bit array

#define rxPin 12
#define txPin 13
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
ros::NodeHandle nh;

//100 for motor 1, 110 for motor 2
//void messageCb( const std_msgs::Empty& toggle_msg){
////  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led
//  digitalWrite(A0, HIGH-digitalRead(A0));
//  digitalWrite(A1, HIGH-digitalRead(A1));
//  mySerial.println("In messageCb");
//  mySerial.println(HIGH-digitalRead(A0));
//  mySerial.println(HIGH-digitalRead(A1));
//} 

void messageCb(const std_msgs::Int16MultiArray& pwm_msg) {
//  mySerial.println("inside correct callback");
  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  analogWrite(9, pwm_msg.data[1]);
}

//ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );
ros::Subscriber<std_msgs::Int16MultiArray> sub("wheelsPWM", &messageCb );
//ros::Subscriber<std_msgs::Int16> sub("onewheel", &messageCb );

void setup()
{
  nh.initNode();
  nh.subscribe(sub);
//  nh.subscribe(sub2);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);

  pinMode(DIR1A, OUTPUT);
  pinMode(DIR1B, OUTPUT);
  pinMode(DIR2A, OUTPUT);
  pinMode(DIR2B, OUTPUT);
  pinMode(DIR3A, OUTPUT);
  pinMode(DIR3B, OUTPUT);
  
  mySerial.begin(9600);
  mySerial.println("Software Serial Started");
  
  
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
