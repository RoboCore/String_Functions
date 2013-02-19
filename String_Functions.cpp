

/*
	RoboCore String Functions Library
		(v1.0 - 30/01/2013)

  Library to manipulate strings

  Released under the Beerware licence
*/


#include "String_Functions.h"

//#define RC_STRING_DEBUG

#define NULL 0


//-------------------------------------------------------------------------------------------------

// Get the length of a string
int StrLength(char* string){
  int length = 0;
  boolean leave = false;

  //find the length of the string
  while(!leave){
    if(string[length] == '\0')
      leave = true;
    else
      length++;
  }
  
  return length;
}

//-------------------------------------------------------------------------------------------------

// Concatenate two strings
//  NOTE: it doesn't change any of the given strings
char* StrConcat(char* str1, char* str2){
  int len1 = StrLength(str1);
  int len2 = StrLength(str2);
  
  //create new temporary string
  char *newstr = (char*)malloc((len1 + len2 + 1) * sizeof(char));
  if(newstr == NULL){
#ifdef RC_STRING_DEBUG
    Serial.println("ERROR in StrConcat: cannot allocate memory!");
#endif
    return "";
  }
  
  //fill string
  newstr[len1+len2] = '\0'; //insert End Of String
  for(int i=0 ; i < len1 ; i++)
    newstr[i] = str1[i];
  for(int i=0 ; i < len2 ; i++)
    newstr[i + len1] = str2[i];
  
  return newstr;
}

//-------------------------------------------------------------------------------------------------

// Removes a character from a string
char* StrRemove(char* string, char c){
  int length = StrLength(string);
  
  //find the number of ocurences
  int count = 0;
  for(int i=0 ; i < length; i++){
    if(string[i] == c)
      count++;
  }
  
  //allocates
  char* res = (char*)malloc((length - count + 1) * sizeof(char));
  if(res == NULL){
#ifdef RC_STRING_DEBUG
    Serial.println("ERROR in StrRemove: cannot allocate memory!");
#endif
    return "";
  }
  
  //assign values
  int index = 0;
  res[length - count] = '\0';
  for(int i=0 ; i < length ; i++){
    if(string[i] != c){
      res[index] = string[i];
      index++;
    }
  }
  
  return res;
}

//-------------------------------------------------------------------------------------------------

// Removes a series of characters from a string
char* StrRemove(char* string, char* characters){
  int length = StrLength(string);
  int lenc = StrLength(characters);
  
  //find the number of ocurences
  int count = 0;
  for(int i=0 ; i < length; i++){
    for(int j=0 ; j < lenc ; j++){
      if(string[i] == characters[j])
        count++;
    }
  }
  
  //allocates
  char* res = (char*)malloc((length - count + 1) * sizeof(char));
  if(res == NULL){
#ifdef RC_STRING_DEBUG
    Serial.println("ERROR in StrRemove: cannot allocate memory!");
#endif
    return "";
  }
  
  //assign values
  int index = 0;
  boolean add;
  res[length - count] = '\0';
  for(int i=0 ; i < length ; i++){
    add = true;
    //check whether to add or not
    for(int j=0 ; j < lenc ; j++){
      if(string[i] == characters[j]){
        add = false;
        break; //avoid more processing
      }
    }
    if(add){
      res[index] = string[i];
      index++;
    }
  }
  
  return res;
}

//-------------------------------------------------------------------------------------------------










