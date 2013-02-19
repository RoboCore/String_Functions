#ifndef RC_STRING_FUNCTIONS
#define RC_STRING_FUNCTIONS

/*
	RoboCore String Functions Library
		(v1.0 - 30/01/2013)

  Library to manipulate strings

  Released under the Beerware licence
*/


#include "Arduino.h" //for Arduino 1.0 and later


//-------------------------------------------------------------------------------------------------

// Get the length of a string
int StrLength(char* string);

//-------------------------------------------------------------------------------------------------

// Concatenate two strings
//  NOTE: it doesn't change any of the given strings
char* StrConcat(char* str1, char* str2);

//-------------------------------------------------------------------------------------------------

// Removes a character from a string
char* StrRemove(char* string, char c);

//-------------------------------------------------------------------------------------------------

// Removes a series of characters from a string
char* StrRemove(char* string, char* characters);

//-------------------------------------------------------------------------------------------------



#endif
