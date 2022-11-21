#include <SoftwareSerial.h>
#define rxPin 5
#define txPin 4
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);


void setup()  {
    // Define pin modes for TX and RX
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);

    

    // Set the baud rate for the SoftwareSerial object

    mySerial.begin(9600);
    Serial.begin(9600);
    

}


void loop() {

    if (mySerial.available() > 0) {

        Serial.write(mySerial.read());
//        Serial.println("");

    }

}
