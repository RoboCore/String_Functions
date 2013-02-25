#ifndef RC_STRING_FUNCTIONS
#define RC_STRING_FUNCTIONS

/*
	RoboCore String Functions Library
		(v1.1 - 25/02/2013)

  Library to manipulate strings

  Released under the Beerware licence


  NOTE: the library uses malloc() to create the strings,
	so one must free the string after using it.
        # can use <Memory.h> to use the PointerList (just
            include it in the main sketch)
            >> see UsingMemory()

  NOTE: more functions (and alternative ones) can be found
	in the <string.h> library



  OBS:	char* str1 = "test";
		//in .DATA section, DO NOT free (because will
			add this address to the free_list)
	char* str2 = (char*)malloc(10);
		//in the HEAP, so CAN be freed
*/


#include "Arduino.h" //for Arduino 1.0 and later
#include <Memory.h>

// bitwise values for StrFind()
#define CASE_SENSITIVE 0
#define CASE_INSENSITIVE (1 << 0)


//-------------------------------------------------------------------------------------------------

// Get the length of a string
int StrLength(char* string);

//-------------------------------------------------------------------------------------------------

// Concatenate two strings
//  NOTE: it doesn't change any of the given strings
//    (returns NULL on error or if given strings are empty, pointer to one of the strings
//          if the other is empty, or the concatenated string)
char* StrConcat(char* str1, char* str2);

//-------------------------------------------------------------------------------------------------

// Finds the position of a character in a string
//  NOTE: by default uses CASE_SENSITIVE comparison
//    (returns -1 if 'string' is empty, 'c' wasn't found or 'c' is NULL)
int StrFind(char* string, char c);
int StrFind(char* string, char c, byte options);


// Finds the position of str2 in str1
//  NOTE: by default uses CASE_SENSITIVE comparison
//    (returns -1 if str2 > str1, str2 is empty or coudn't find)
int StrFind(char* str1, char* str2);
int StrFind(char* str1, char* str2, byte options);

//-------------------------------------------------------------------------------------------------

// Parses the string to get the string at the desired index (1 based)
//    (returns NULL if the string is empty (length of 0), if NULL delimiter or
//          if the index is not valid, or the desired string)
char* StrParser(char* string, char delimiter, int index);

//-------------------------------------------------------------------------------------------------

// Get the length of the string (of given index >> 1 based) in the string to parse
//    (returns 0 if empty string, NULL delimiter or invalid index, or the string length)
int StrParserLength(char* string, char delimiter, int index);

//-------------------------------------------------------------------------------------------------

// Return the number of valid strings to parse
//    (returns 0 if empty string or NULL delimiter, or the number of strings)
int StrParserQty(char* string, char delimiter);

//-------------------------------------------------------------------------------------------------

// Removes a character from a string
//    (returns NULL on error or if 'string' is empty, pointer to 'string' if 'c' is NULL)
char* StrRemove(char* string, char c);

// Removes a series of characters from a string
//    (returns NULL on error or if given string is empty, pointer to 'string' if 'characters' is empty)
char* StrRemove(char* string, char* characters);

//-------------------------------------------------------------------------------------------------

// Check whether is using <Memory.h>
boolean UsingMemory();

//-------------------------------------------------------------------------------------------------


#endif
