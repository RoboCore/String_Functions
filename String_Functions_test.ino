

#include "String_Functions.h"

//-------------------------------------------------------------------------------------------------



void setup(){
  Serial.begin(9600);
//  pinMode(13, OUTPUT);
//  digitalWrite(13, LOW);
}



void loop(){
  
  char* teste = "ab-cd-ef gh ij kl";
  Serial.println(teste);
  Serial.println(StrRemove(teste, '-'));
  Serial.println(StrRemove(teste, ' '));
  Serial.println(StrRemove(teste, " -"));
  
  Serial.println("---FIM---");
  while(1){
  }
}





