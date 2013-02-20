

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


/*
                  TEST 20/02/13

Include <Hex_Strings.h> only to use memory debug, but the library
    includes <String_Functions.h>, so cannot include this library locally

>> MUST free() the strings because malloc was used, otherwise has memory leak
        (last two - teste, teste2 - might be handled automatically by progam >> not tested)


OUTPUT without free():
#1
[mem] 1749
ab-cd-ef gh ij kl
abcdef gh ij kl
#2
[mem] 1731
ab-cd-efghijkl
#3
[mem] 1714
abcdefghijkl
#4
[mem] 1699
ab-cd-ef gh ij kl123456
#5
[mem] 1673
#6
[mem] 1673


OUTPUT with free():
#1
[mem] 1751
ab-cd-ef gh ij kl
abcdef gh ij kl
#2
[mem] 1751
ab-cd-efghijkl
#3
[mem] 1751
abcdefghijkl
#4
[mem] 1751
ab-cd-ef gh ij kl123456
#5
[mem] 1751
#6
[mem] 1852


-----------------------------

#include <Hex_Strings.h>

  Serial.println("#1");
  AvailableMemory(&Serial, true);
  
  char* teste = "ab-cd-ef gh ij kl";
  Serial.println(teste);
  
  char* temp = StrRemove(teste, '-');
  Serial.println(temp);
  free(temp); // <--------------------------
  Serial.println("#2");
  AvailableMemory(&Serial, true);
  
  temp = StrRemove(teste, ' ');
  Serial.println(temp);
  free(temp); // <--------------------------
  Serial.println("#3");
  AvailableMemory(&Serial, true);
  
  temp = StrRemove(teste, " -");
  Serial.println(temp);
  free(temp); // <--------------------------
  Serial.println("#4");
  AvailableMemory(&Serial, true);
  
  
  char* teste2 = "123456";
  char* conc = StrConcat(teste, teste2);
  Serial.println(conc);
  free(conc); // <--------------------------
  Serial.println("#5");
  AvailableMemory(&Serial, true);
  
  free(teste); // <--------------------------
  free(teste2); // <--------------------------
  Serial.println("#6");
  AvailableMemory(&Serial, true);
*/


