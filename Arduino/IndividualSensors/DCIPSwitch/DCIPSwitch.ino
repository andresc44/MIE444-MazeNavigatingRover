const int sw_pin_1   =  8;
const int sw_pin_2   =  9;

int sw_state_1 = 0;
int sw_state_2 = 0;

void setup() 
{


pinMode(sw_pin_1, INPUT_PULLUP);  // define pin 8
pinMode(sw_pin_2, INPUT_PULLUP);  // define pin 9
Serial.begin(9600);
}


void loop()
{
  sw_state_1 = digitalRead(sw_pin_1);
  sw_state_2 = digitalRead(sw_pin_2);
  
  
  if (sw_state_1 == LOW && sw_state_2 == LOW) 
  {
    Serial.print("Path 0");
  }
  else if (sw_state_1 == LOW && sw_state_2 == HIGH)
  {
    Serial.print("Path 1");
  }
  else if (sw_state_1 == HIGH && sw_state_2 == LOW)
  {
    Serial.print("Path 2");
  }
  else if (sw_state_1 == HIGH && sw_state_2 == HIGH)
  {
    Serial.print("Path 3"); 
  }
}
