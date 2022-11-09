//direction the robot will go in relative to car body
uint8_t pwm_array[3] = {0, 0, 0}; //initialize pwm array


void DC_Motor_Setup() {
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
  
  // leave for liam
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
  analogWrite(EN1, pwm[0]);
  analogWrite(EN2, pwm[1]);
  analogWrite(EN3, pwm[2]);
}

void Move_Robot (uint8_t movement[]) {
  //sets direction of motor as clockwise or counterclock
  //UPDATE 0 to 255 and -255 to 0
  // new code can say if its <255 or >255 change direction
  if (movement[0]) {
    digitalWrite(DIR1A, HIGH);
    digitalWrite(DIR1B, LOW);
  }
  else {
    digitalWrite(DIR1A, LOW);
    digitalWrite(DIR1B, HIGH);
  }
  if (movement[2]) {
    digitalWrite(DIR2A, HIGH);
    digitalWrite(DIR2B, LOW);
  }
  else {
    digitalWrite(DIR2A, LOW);
    digitalWrite(DIR2B, HIGH);
  }
  if (movement[4]) {
    digitalWrite(DIR3A, HIGH);
    digitalWrite(DIR3B, LOW);
  }
  else {
    digitalWrite(DIR3A, LOW);
    digitalWrite(DIR3B, HIGH);
  }
  pwm_array[0] = movement[1];
  pwm_array[1] = movement[3];
  pwm_array[2] = movement[5];
  //Ajust_PWM({{movement[1]}, {movement[3]}, {movement[5]}});
  Ajust_PWM(pwm_array);
}
