

/*
	RoboCore String Functions Library
		(v1.3 - 27/02/2013)

  Library to manipulate strings
    (tested with Arduino 0022 and 1.0.1)

  Released under the Beerware licence
  Written by François


  NOTE: the library uses malloc() to create the strings and
        the Pointer List in <Memory.h> is usedby default .
        To use regular malloc(), undefine USE_POINTER_LIST
        in <Memory.h>

  NOTE: more functions (and alternative ones) can be found
	in the <string.h> library



  OBS:	char* str1 = "test";
		//in .DATA section, DO NOT free (because will
			add this address to the free_list)
	char* str2 = (char*)malloc(10);
		//in the HEAP, so CAN be freed
*/

#include "String_Functions.h"


//-------------------------------------------------------------------------------------------------

// Read a string from serial until buffer is full, eol is reached (if eol not NULL) or
//   no more characters in the serial buffer (if eol is NULL)
//  (returns the string length)
//  NOTE: it is recommended to create the buffer with 1 adicional char because
//        the code adds the NULL termination
//         (ex: desired size = 30 >> create with 31 and pass this value as parameter)
int ReadFromSerial(HardwareSerial* serial, char* buffer, int buffer_size, char eol){
  int count = 0;
  if(eol == NULL){ //default value, means wait for full buffer or no more characters
    while(serial->available()){
      buffer[count++] = serial->read();
      
      delay(RC_READ_SERIAL_DElAY); //wait for all data to arrive
      
      //check for buffer overflow
      if(count >= buffer_size){
        //flush serial buffer
        while(serial->available()){
          char c = serial->read();
        }
        break; //exit main while loop
      }
    }
    
    //add '\0' at the end (NULL terminated string)
    buffer[buffer_size - 1] = '\0';
    if(count < buffer_size)
      buffer[count] = '\0';
    
    //correction for exact buffer size
    if(count == buffer_size)
      count--;
    
    return count;
  } else { //wait for eol and ignore if serial buffer is empty
    char c = eol - 1; //assign a different value for the first time
    while(c != eol){
      if(serial->available()){
        c = serial->read();
        buffer[count++] = c;
      }
      
      delay(RC_READ_SERIAL_DElAY); //wait for all data to arrive
      
      //check for buffer overflow
      if(count >= buffer_size){
        //flush serial buffer
        while(serial->available()){
          c = serial->read();
        }
        break; //exit main while loop
      }
    }
    
    //add '\0' at the end (NULL terminated string)
    buffer[buffer_size - 1] = '\0';
    if(count < buffer_size)
      buffer[count - 1] = '\0'; //(-1) because EOL is included
    
    return (count - 1); //(-1) because EOL is included
  }
}

//-------------------------------------------------------------------------------------------------

//IMPORTANT: DO NOT forget to cast to (byte) when calling overloads with 'option'

int StrCompare(char* str1, char* str2){
  return StrCompare(str1, str2, 0, StrLength(str2), CASE_SENSITIVE);
}


int StrCompare(char* str1, char* str2, byte options){
  return StrCompare(str1, str2, 0, StrLength(str2), options);
}

//-----------------------------------

int StrCompare(char* str1, char* str2, int start){
  return StrCompare(str1, str2, start, StrLength(str2), CASE_SENSITIVE);
}


int StrCompare(char* str1, char* str2, int start, byte options){
  return StrCompare(str1, str2, start, StrLength(str2), options);
}

//-----------------------------------

int StrCompare(char* str1, char* str2, int start, int length){
  return StrCompare(str1, str2, start, length, CASE_SENSITIVE);
}

//-----------------------------------

// Compares str2 with str1 and with given options, starting from start in str1
//   and until length or end of str2 is reached
//  NOTE: by default start = 0, length = StrLength(str2) and is CASE_SENSITIVE
//    (returns the number of matched characters (0 if none matched) or
//      -1 on errror)
//  NOTE: if(return == StrLength(str2)), str2 was found in str1. Otherwise
//          only part (or nothing) of str2 was found
int StrCompare(char* str1, char* str2, int start, int length, byte options){
  //validate input
  if(start < 0)
    return -1;
  if(length <= 0)
    return -1;
  
  //get length of the strings
  int len1 = StrLength(str1);
  int len2 = StrLength(str2);
  
  //check strings
  if((len1 == 0) || (len2 == 0))
    return -1;
  else if(len2 > len1)
    return -1;
  
  //check total length
  if(len1 < (start + len2))
    return -1; 
  
  //start comparison
  int match = 0;
  char c1, c2;
  for(int i=0 ; i < length ; i++){
    //search until end of str2 or length
    if(i >= len2)
      break;
    
    //get chars to compare
    c1 = str1[i + start]; //get with offset
    c2 = str2[i]; //get unchanged
    
    //binary comparison
    if((c1 != c2) && (options ^ CASE_INSENSITIVE)){ //different character and case SENSITIVE
      break;
    } else if((c1 != c2) && (options & CASE_INSENSITIVE)){ //case INSENSITIVE comparison
      if((c1 >= 97) && (c1 <= 122)) //'a' to 'z'
        c1 -= 32; //convert to 'A' to 'Z'
      
      if((c2 >= 97) && (c2 <= 122)) //'a' to 'z'
        c2 -= 32; //convert to 'A' to 'Z'
      
      if(c1 != c2) //different characters
        break;
    }
    
    match++; //if reached here, means characters are equal
  }
  
  return match;
}

//-------------------------------------------------------------------------------------------------

// Concatenate two strings
//  NOTE: it doesn't change any of the given strings
//    (returns NULL on error or if given strings are empty, pointer to one of the strings
//          if the other is empty, or the concatenated string)
char* StrConcat(char* str1, char* str2){
  int len1 = StrLength(str1);
  int len2 = StrLength(str2);
  
  //check strings
  if((len1 == 0) && (len2 == 0))
    return NULL;
  else if(len1 == 0)
    return str2;
  else if(len2 == 0)
    return str1;
  
  //create new temporary string
#ifdef USE_POINTER_LIST
  PointerList::Initialize();
  char* newstr = (char*)Mmalloc((len1 + len2 + 1) * sizeof(char));
#else
  char* newstr = (char*)malloc((len1 + len2 + 1) * sizeof(char));
#endif

  if(newstr == NULL){
#ifdef RC_STRING_DEBUG
    Serial.println("ERROR in StrConcat: cannot allocate memory!");
#endif
    return NULL;
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

// Finds the position of a character in a string
//  NOTE: by default uses CASE_SENSITIVE comparison
//    (returns -1 if 'string' is empty, 'c' wasn't found or 'c' is NULL)
int StrFind(char* string, char c){
  return StrFind(string, c, CASE_SENSITIVE);
}


// Finds the position of a character in a string
//    (returns -1 if 'string' is empty, 'c' wasn't found or 'c' is NULL)
int StrFind(char* string, char c, byte options){
  int length = StrLength(string);
  int pos = -1;
  
  //check length
  if(length == 0)
    return pos;
  if(c == NULL)
    return pos;
  
  //find character
  for(int i=0 ; i < length ; i++){
    //binary comparison
    if(c == string[i]){
      pos = i;
      break;
    }
    
    //case INSENSITIVE comparison
    if(options & CASE_INSENSITIVE){
      if((c >= 65) && (c <= 90)){ //'A' to 'Z'
        if((c + 32) == string[i]){
          pos = i;
          break;
        }
      }
      if((c >= 97) && (c <= 122)){ //'a' to 'z'
        if((c - 32) == string[i]){
          pos = i;
          break;
        }
      }
    }
  }
  
  return pos;
}

//-----------------------------------

// Finds the position of str2 in str1
//  NOTE: by default uses CASE_SENSITIVE comparison
//    (returns -1 if str2 > str1, str2 is empty or coudn't find)
int StrFind(char* str1, char* str2){
  return StrFind(str1, str2, CASE_SENSITIVE);
}


// Finds the position of str2 in str1
//    (returns -1 if str2 > str1, str2 is empty or coudn't find)
int StrFind(char* str1, char* str2, byte options){
  int len1 = StrLength(str1);
  int len2 = StrLength(str2);
  int pos = -1;
  
  //check length
  if(len1 < len2)
    return pos;
  if(len2 == 0)
    return pos;
  
  //find character
  boolean began = false; //true when found the first character
  char c1, c2;
  for(int i=0 ; i < len1 ; i++){
    //check if already found
    if((pos != -1) && ((i - pos) >= len2))
      break;
    
    //get chars to compare
    c1 = str1[i]; //get unchanged
    if(!began) //if not yet found, compare with first
      c2 = str2[0];
    else //otherwise get next
      c2 = str2[i - pos];
    
    //binary comparison
    if(c1 == c2){
      if(!began){ //assign once
        pos = i;
        began = true; //set
      }
    } else if(began && (options ^ CASE_INSENSITIVE)){ //broke sequence and is CASE_SENSITIVE, so find next
      pos = -1;
      began = false; //reset
    }
    
    //case INSENSITIVE comparison
    if(options & CASE_INSENSITIVE){
      if((c1 >= 97) && (c1 <= 122)) //'a' to 'z'
        c1 -= 32; //convert to 'A' to 'Z'
      
      if((c2 >= 97) && (c2 <= 122)) //'a' to 'z'
        c2 -= 32; //convert to 'A' to 'Z'
      
      if(c1 == c2){
        if(!began){ //assign once
          pos = i;
          began = true; //set
        }
      } else if(began){ //broke sequence (already checked for binary), so find next
        pos = -1;
        began = false; //reset
      }
    }
  }
  
  return pos;
}

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

// Parses the string to get the string at the desired index (1 based)
//    (returns NULL if the string is empty (length of 0), if NULL delimiter or
//          if the index is not valid, or the desired string)
char* StrParser(char* string, char delimiter, int index){
  //NOTE: it is preferable to use the same (almost) code of StrParserLength() to avoid
  //        growing the stack and more processing
  
  //check if valid length
  int length = StrLength(string);
  if(length <= 0) //no string
    return NULL;
  
  //check delimiter
  if(delimiter == NULL)
    return NULL;
  
  //parse
  int current_string = 1; //assume at least one exists, even if no delimiter was found
  if(string[0] == delimiter) //oups, the string begins with a delimiter, so must reset the counter
    current_string = 0;
  boolean found_delimiter = false;
  int string_length = 0; //the length of the desired string
  int pos = -1; //the position were the desired string was found
  for(int i=0 ; (i < length) && (current_string <= index) ; i++){
    if(string[i] == delimiter){
      found_delimiter = true; //found one!
    } else if(found_delimiter){
      found_delimiter = false; //reset
      current_string++; //one more string!
    }
    
    //leave loop if the string was already found
    if(current_string > index)
      break;
    
    //if is the desired string, add one character
    if((current_string == index) && !found_delimiter)
      string_length++;
    
    //store the initial position of the desired string
    if((current_string == index) && (pos == -1)) //must store only once
      pos = i;
  }
  
  //check if the string was found
  if(pos == -1){ // OR (string_length == 0)
    return NULL;
  }
  
  //create new temporary string
#ifdef USE_POINTER_LIST
  PointerList::Initialize();
  char* newstr = (char*)Mmalloc((string_length + 1) * sizeof(char)); //allocate memory
#else
  char* newstr = (char*)malloc((string_length + 1) * sizeof(char)); //allocate memory
#endif

  if(newstr == NULL){
#ifdef RC_STRING_DEBUG
    Serial.println("ERROR in StrParse: cannot allocate memory!");
#endif
    return NULL;
  }
  
  //fill string
  newstr[string_length] = '\0'; //insert End Of String
  for(int i=0 ; i < string_length ; i++){
    newstr[i] = string[pos+i];
  }
  
  return newstr;
}

//-------------------------------------------------------------------------------------------------

// Get the length of the string (of given index >> 1 based) in the string to parse
//    (returns 0 if empty string, NULL delimiter or invalid index, or the string length)
int StrParserLength(char* string, char delimiter, int index){
  //check if valid length
  int length = StrLength(string);
  if(length <= 0) //no string
    return 0;
  
  //check delimiter
  if(delimiter == NULL)
    return 0;
  
  //find number of strings
  int current_string = 1; //assume at least one exists, even if no delimiter was found
  if(string[0] == delimiter) //oups, the string begins with a delimiter, so must reset the counter
    current_string = 0;
  boolean found_delimiter = false;
  int string_length = 0;
  for(int i=0 ; (i < length) && (current_string <= index) ; i++){
    if(string[i] == delimiter){
      found_delimiter = true; //found one!
    } else if(found_delimiter){
      found_delimiter = false; //reset
      current_string++; //one more string!
    }
    
    //leave loop if the string was already found
    if(current_string > index)
      break;
    
    //if is the desired string, add one character
    if((current_string == index) && !found_delimiter)
      string_length++;
  }
  
  return string_length;
}

//-------------------------------------------------------------------------------------------------

// Get the number of valid strings to parse
//    (returns 0 if empty string or NULL delimiter, or the number of strings)
int StrParserQty(char* string, char delimiter){
  //check if valid length
  int length = StrLength(string);
  if(length <= 0) //oups, I guess there was no string after all
    return 0;
  
  //check delimiter
  if(delimiter == NULL)
    return 0;
  
  //find number of strings
  int num_strings = 1; //assume at least one exists, even if no delimiter was found
  if(string[0] == delimiter) //oups, the string begins with a delimiter, so must reset the counter
    num_strings = 0;
  boolean found_delimiter = false;
  for(int i=0 ; i < length ; i++){
    if(string[i] == delimiter){
      found_delimiter = true; //found one!
    } else if(found_delimiter){
      found_delimiter = false; //reset
      num_strings++; //one more string!
    }
  }
  
  return num_strings;
}

//-------------------------------------------------------------------------------------------------

// Removes a character from a string
//    (returns NULL on error or if 'string' is empty, pointer to 'string' if 'c' is NULL)
char* StrRemove(char* string, char c){
  int length = StrLength(string);
  
  //check length
  if(length == 0)
    return NULL;
  if(c == NULL)
    return string;
  
  //find the number of ocurences
  int count = 0;
  for(int i=0 ; i < length; i++){
    if(string[i] == c)
      count++;
  }
  
  //allocates
#ifdef USE_POINTER_LIST
  PointerList::Initialize();
  char* res = (char*)Mmalloc((length - count + 1) * sizeof(char));
#else
  char* res = (char*)malloc((length - count + 1) * sizeof(char));
#endif

  if(res == NULL){
#ifdef RC_STRING_DEBUG
    Serial.println("ERROR in StrRemove: cannot allocate memory!");
#endif
    return NULL;
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

//-----------------------------------

// Removes a series of characters from a string
//    (returns NULL on error or if given string is empty, pointer to 'string' if 'characters' is empty)
char* StrRemove(char* string, char* characters){
  int length = StrLength(string);
  int lenc = StrLength(characters);
  
  //check length
  if(length == 0)
    return NULL;
  if(lenc == 0)
    return string;
  
  //find the number of ocurences
  int count = 0;
  for(int i=0 ; i < length; i++){
    for(int j=0 ; j < lenc ; j++){
      if(string[i] == characters[j])
        count++;
    }
  }
  
  //allocates
#ifdef USE_POINTER_LIST
  PointerList::Initialize();
  char* res = (char*)Mmalloc((length - count + 1) * sizeof(char));
#else
  char* res = (char*)malloc((length - count + 1) * sizeof(char));
#endif

  if(res == NULL){
#ifdef RC_STRING_DEBUG
    Serial.println("ERROR in StrRemove: cannot allocate memory!");
#endif
    return NULL;
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









