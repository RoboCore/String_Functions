
/*
	RoboCore - Read From Serial example
		(25/03/2013)

  Written by François

  Read a message from serial and store it into a buffer.
  # use only one of the two ReadFromSerial() calls below
  
*/

#include <String_Functions.h>

const char EOL = '#';
const int buffer_size = 6; //size of 5 + 1 for NULL termination
char buffer[buffer_size];

extern unsigned int RC_READ_SERIAL_DELAY; //in [us]

void setup(){
  Serial.begin(9600);
  
  //try changing this value to see the result of the first ReadFromSerial() method
//  RC_READ_SERIAL_DELAY = 1; //in [us] (default of 10000)
}

void loop(){
  if(Serial.available()){
    Serial.print(ReadFromSerial(&Serial, buffer, buffer_size)); //the length of the received message
//    Serial.print(ReadFromSerial(&Serial, buffer, buffer_size, EOL)); //the length of the received message
    Serial.print(":");
    Serial.print(buffer);
    Serial.println('*'); //to indicate the end of the string
  }
}
