char val = 0; //holds ascii from serial line

signed char i = 0; // motor 1 speed
signed char j = 0; // motor 2 speed

void setup() 
{
  Serial.begin(9600);
  Serial.println("Hello I am alive");
  set_speedA(i);
  set_speedB(j);
}

//Speeds are between -32 and 32
void set_speedA(signed char speed) 
{
  if((speed > -128) && (speed < 128))
  {
     analogWrite(9, 128 + speed);
     analogWrite(10, 128 + speed);
     TCCR1A |= B00110000;  //invert PWM output
  }
}
void set_speedB(signed char speed)
{
  if((speed > -128) && (speed < 128))
  {
     analogWrite(5, 128 + speed);
     analogWrite(6, 128 + speed);
     TCCR0A |= B00110000;  //invert PWM output
  }
}

void loop()
{   
  if (Serial.available())
  {
  val = Serial.read();
  Serial.println(val);
  if (val == 'w')
    {
      i = i + 8;
      j = j + 8;
      set_speedA(i);
      set_speedB(j);
    }
    else if(val == 's')
    {
      i = i - 8;
      j = j - 8;
      set_speedA(i);
      set_speedB(j);
    }
    else if(val == 'd')
    {
      i = i + 8;
      j = j - 8;
      set_speedA(i);
      set_speedB(j);
    }
    else if(val == 'a')
    {
      i = i - 8;
      j = j + 8;
      set_speedA(i);
      set_speedB(j);
    }
    else if(val == 'k')
    {
      i = 0;
      j = 0;
      set_speedA(i);
      set_speedB(j);
    }
  }
}
