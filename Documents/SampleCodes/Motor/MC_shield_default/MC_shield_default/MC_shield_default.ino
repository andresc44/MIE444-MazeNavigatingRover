void setup() {
  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin
  //setup Channel A
  pinMode(12, OUTPUT); //Initiates the Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates the Brake channel A pin
}

void loop() {
  runA(255, false);
  runB(255, true);
  delay(3000);
  //call fullstop
  fs();
  delay(1000);  
}

void runA(int speed, boolean rev) {  
  if(rev) {
    //Establishes backward direction of Channel A
    digitalWrite(12, LOW);
  }else {
    //Establishes forward direction of Channel A
    digitalWrite(12, HIGH); 
  }
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, speed);   //Spins the motor on Channel A at full speed
}  

void runB(int speed, boolean rev) {
  if(rev) {
    digitalWrite(13, LOW); //Establishes backwards direction of Channel B
  }else{
    digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  }
   
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, speed);   //Spins the motor on Channel B at full speed 
}

//fullstop
void fs(){
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);

}

