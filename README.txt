
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



