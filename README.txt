
	RoboCore String Functions Library
		(v1.3 - 27/02/2013)

  Library to manipulate strings
    (tested with Arduino 0022 and 1.0.1)

  Released under the Beerware licence


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



