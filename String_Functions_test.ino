

#include <Memory.h>
#include "String_Functions.h"

// see README.txt to not use the Pointer List

//-------------------------------------------------------------------------------------------------


void setup(){
  Serial.begin(9600);
}



void loop(){
  
  Serial.print("<Memory> ");
  if(UsingPointerList())
    Serial.println("OK");
  else
    Serial.println("no");
  AvailableMemory(&Serial, true);
  Serial.println();
 
/*
  Serial.println("#1"); //*********************************************
  
  char* teste = "ab-cd-ef gh ij kl"; // .DATA section
  Serial.println(teste);
  
  char* temp = StrRemove(teste, '-'); // HEAP
  Serial.println(temp);
//  free(temp); // <--------------------------
  
  temp = StrRemove(teste, ' '); // HEAP
  Serial.println(temp);
//  free(temp); // <--------------------------
  
  temp = StrRemove(teste, " -"); // HEAP
  Serial.println(temp);
//  free(temp); // <--------------------------
  
  
  char* teste2 = "123456"; // .DATA section
  char* conc = StrConcat(teste, teste2); // HEAP
  Serial.println(conc);
//  free(conc); // <--------------------------
*/

  Serial.println("#2"); //*********************************************

  char* teste = NULL;
  char* teste2 = NULL;
  
  teste = "teste/lala"; // .DATA section
  Serial.println();
  AvailableMemory(&Serial, true);
  Serial.print(teste); Serial.print(" >> "); Serial.println(StrParserQty(teste, '/'));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', 1));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', 2));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', 3));
      teste2 = StrParser(teste, '/', 1); // HEAP
      Serial.print("\t1/-"); Serial.print(teste2); Serial.println("-");
      teste2 = StrParser(teste, '/', 2); // HEAP
      Serial.print("\t2/-"); Serial.print(teste2); Serial.println("-");
      teste2 = StrParser(teste, '/', -1); // HEAP
      Serial.print("\t-1/-"); Serial.print(teste2); Serial.println("-");
  Serial.print(teste); Serial.print(" >> "); Serial.println(StrParserQty(teste, '#'));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '#', 1));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '#', 2));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', -1));
      teste2 = StrParser(teste, '#', 1); // HEAP
      Serial.print("\t1#-"); Serial.print(teste2); Serial.println("-");
//  free(teste2);


  teste = "/teste"; // .DATA section
  Serial.println();
  AvailableMemory(&Serial, true);
  Serial.print(teste); Serial.print(" >> "); Serial.println(StrParserQty(teste, '/'));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', 1));
      teste2 = StrParser(teste, '/', 1); // HEAP
      Serial.print("\t1/-"); Serial.print(teste2); Serial.println("-");
//  free(teste2);


  teste = "/"; // .DATA section
  Serial.println();
  AvailableMemory(&Serial, true);
  Serial.print(teste); Serial.print(" >> "); Serial.println(StrParserQty(teste, '/'));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', 1));
      teste2 = StrParser(teste, '/', 1); // HEAP
      Serial.print("\t1/-"); Serial.print(teste2); Serial.println("-");
//  free(teste2);
  
  
  teste = "lala/"; // .DATA section
  Serial.println();
  AvailableMemory(&Serial, true);
  Serial.print(teste); Serial.print(" >> "); Serial.println(StrParserQty(teste, '/'));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', 1));
      teste2 = StrParser(teste, '/', 1); // HEAP
      Serial.print("\t1/-"); Serial.print(teste2); Serial.println("-");
//  free(teste2);
  
  
  //remove test >> remove last string from the heap
  Serial.println();
  PointerList::DisplayList(&Serial);
  Mfree(teste2);
  Serial.print("*remove "); Serial.println((int)teste2, HEX);
  PointerList::DisplayList(&Serial);
  
  
  teste = "teste"; // .DATA section
  Serial.println();
  AvailableMemory(&Serial, true);
  Serial.print(teste); Serial.print(" >> "); Serial.println(StrParserQty(teste, '/'));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', 1));
      teste2 = StrParser(teste, '/', 1); // HEAP
      Serial.print("\t1/-"); Serial.print(teste2); Serial.println("-");
//  free(teste2);
  
  
  teste = "////"; // .DATA section
  Serial.println();
  AvailableMemory(&Serial, true);
  Serial.print(teste); Serial.print(" >> "); Serial.println(StrParserQty(teste, '/'));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', 1));
      teste2 = StrParser(teste, '/', 1); // HEAP
      Serial.print("\t1/-"); Serial.print(teste2); Serial.println("-");
//  free(teste2);
  
  
  teste = "/aaa///"; // .DATA section
  Serial.println();
  AvailableMemory(&Serial, true);
  Serial.print(teste); Serial.print(" >> "); Serial.println(StrParserQty(teste, '/'));
  Serial.print("\t\t|| "); Serial.println(StrParserLength(teste, '/', 1));
      teste2 = StrParser(teste, '/', 1); // HEAP
      Serial.print("\t1/-"); Serial.print(teste2); Serial.println("-");
//  free(teste2);
  
  
  Serial.println();
  Serial.println("#3"); //*********************************************
  AvailableMemory(&Serial, true);
  
  char* test = NULL;
  test = "STRING to search F"; // .DATA section
  Serial.println(test);
  Serial.print("s: "); Serial.print(StrFind(test, 's')); Serial.print(" | "); Serial.println(StrFind(test, 's', CASE_INSENSITIVE));
  Serial.print("NULL: "); Serial.print(StrFind(test, '\0')); Serial.print(" | "); Serial.println(StrFind(test, '\0', CASE_INSENSITIVE));

  Serial.println();  
  char* str = NULL;
  str = "SeArCh"; // .DATA section
  Serial.println(str);
  Serial.print("s: "); Serial.print(StrFind(test, str)); Serial.print(" | "); Serial.println(StrFind(test, str, CASE_INSENSITIVE));
  Serial.print("(same): "); Serial.print(StrFind(str, str)); Serial.print(" | "); Serial.println(StrFind(str, str, CASE_INSENSITIVE));
  
  
  Serial.println();
  Serial.println("#4"); //*********************************************
  AvailableMemory(&Serial, true);
  
  Serial.println(StrCompare("AbCdE", "Bc")); //return 0
  Serial.println(StrCompare("AbCdE", "Bc", (byte)CASE_INSENSITIVE)); //return 0
  Serial.println(StrCompare("AbCdE", "aB")); //return 0
  Serial.println(StrCompare("AbCdE", "aB", (byte)CASE_INSENSITIVE)); //return 2
  
  Serial.println();
  Serial.println(StrCompare("AbCdE", "Bc", 1)); //return 0
  Serial.println(StrCompare("AbCdE", "Bc", 1, (byte)CASE_INSENSITIVE)); //return 2 (!!! must cast to byte to call proper function)
  Serial.println(StrCompare("AbCdE", "Bc", 1, 2, CASE_INSENSITIVE)); //return 2
  
  Serial.println();
  Serial.println(StrCompare("AbCdE", "Bc", 1, 4)); //return 0
  Serial.println(StrCompare("AbCdE", "bC", 1, 4)); //return 2
  Serial.println(StrCompare("AbCdE", "Bc", 1, 3, CASE_INSENSITIVE)); //return 2
  Serial.println(StrCompare("AbCdE", "Bc", 1, 1, CASE_INSENSITIVE)); //return 1
  Serial.println(StrCompare("AbCdE", "Bc", -1, 3, CASE_INSENSITIVE)); //return -1
  
  Serial.println();
  Serial.println(StrCompare("Bc", "AbCdE", 1, 3, CASE_INSENSITIVE)); //return -1
  Serial.println(StrCompare("AbCdE", "Bc", 3, 3, CASE_INSENSITIVE)); //return 0
  Serial.println(StrCompare("AbCdE", "Bc", 4, 3, CASE_INSENSITIVE)); //return -1
  
  
  
  Serial.println("\n---FIM---");
  Serial.print("count: "); Serial.println(PointerList::ListCount());
  PointerList::DisplayList(&Serial);
  MReset();
  PointerList::DisplayList(&Serial);
  AvailableMemory(&Serial, true);
  while(1){
  }
}


