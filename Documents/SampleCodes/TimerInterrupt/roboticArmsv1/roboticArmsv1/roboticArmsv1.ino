#include <Servo.h>

Servo myservo1, myservo2;

char pre2 = 0;
char spd = 10; //speed of robotic arms

unsigned char num1,num2;
unsigned char cur1,cur2;


void setup() 
{ 
  Serial.begin(9600);
  
  // servo1
  cur1 = 90; num1 = cur1;
  myservo1.attach(9); myservo1.write(cur1);
  // servo 2
  cur2 = 90; num2 = cur2;
  myservo2.attach(10); myservo2.write(cur2);
  
  // initialize timer0 
  noInterrupts();           // disable all interrupts
  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 50;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS02) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  interrupts();             // enable all interrupts  
} 

ISR(TIMER0_COMPA_vect)
{
   pre2 += 1;
   
   if (pre2 == 1*spd)
   {
     if (cur1 < num1)
     {
       cur1++;
       myservo1.write(cur1);
     }
     else if (cur1 > num1)
     {
       cur1--;
       myservo1.write(cur1);
     }    
     // reached destination, could send confirmation once
   }
   else if (pre2 == 2*spd)
   {
     if (cur2 < num2)
     {
       cur2++;
       myservo2.write(cur2);
     }
     else if (cur2 > num2)
     {
       cur2--;
       myservo2.write(cur2);
     }
     pre2 = 0;
   }
} 
 
void loop() 
{
  
    if ( Serial.available()>1) 
    {
      char code = Serial.read();
      char num = Serial.read();
      
      //Serial.print(code);
      //Serial.println(num);
      
      //should clear serial buffer
      
      if (code == 'A')
      {       
        //Serial.print("set servo A: ");
        //Serial.println(int(num));
        num1 = int(num);
      }
      if (code == 'B')
      {       
        //Serial.print("set servo B: ");
        //Serial.println(int(num));
        num2 = int(num);
      }      
      if (code == 'S')
      {       
        spd = num;
      }      
    }

}

