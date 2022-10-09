
String cmdStr;

void loop() {
      
  if(Serial.available() > 0) {
    cmdStr = Serial.readString();
    
    if(cmdStr.charAt(0) == '1') {        
      Serial.println("on!");
    } 
    else if(cmdStr.charAt(0) == '0') {  
      Serial.println("off!");
    }
    else if(cmdStr.charAt(0) == 'd') {
      // Remove characters to get only the inch distance value
      cmdStr.remove(0, 3);
      
      MoveForward(cmdStr.toFloat());

      Serial.println("d");
    } 
    else if(cmdStr.charAt(0) == 'i') {
      // We want to read from our IR sensor
      Serial.println("read IR");
    }


  }

  delay(1);
}
