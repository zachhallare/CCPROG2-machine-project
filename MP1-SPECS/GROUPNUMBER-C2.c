/*
    GROUP NUMBER (2 digits):
    DATE SUBMITTED         :

    LASTNAME1, FIRSTNAME1:                          SECTION1:
    LASTNAME1, FIRSTNAME2:                          SECTION2:

    NOTE: encode ONLY your NAME if this code is for your own individual solution
          encode BOTH names and sections this code is for your GROUP's final solution

    CCPROG2 MP Solution for Challenge #2 (C2)  
        
    You should compile this C source file in the command line using -Wall and -o as compiler options, for example:
         C:\CCPROG2>gcc -Wall -Wall 01-C2.c 01-C2.exe

    You should run the exe file in the command line with input and output redirection, for example:
         C:\CCPROG2>01-C2 < ACorig.txt > AC.txt    
          
    where 01-C2.exe is the student's executable file (01 is the 2 digit group number),
    ACorig.txt is the source file, and AC.txt is the destination file.
  
    The < (less than symbol) is for input redirection, and the > (greater than symbol) is for
    output redirection.
  
    Your program should  
    1. read via scanf() the date entry as a string.  It should also write via printf() the date as a string.     
    2. use a 1D array of strings to store the date values, 
       use a 2D array of doubles for the OHLC values, and 
       use a 1D array of doubles to store the volume values.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Do NOT include other header files 


/* 
	HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
	
	1. You are NOT allowed to use library functions that were NOT discussed in our class.
	2. You must apply arrays and strings in solving Challenge #2. 
	3. Do NOT use the following yet for this particular challenge:
	     a. struct data type
	     b. file processing functions such as fopen(), fclose(), etc.
	3. Apply divide-and-conquer technique by segregating your program's logic into functions.
	   A solution where all the logic are found only in the main() function 
	   will result to a 2-point deduction!
	5. Document your functions with SENSIBLE comments. Each function definition must
	   be PRECEDED by an online documentation (in the form comments) describing
	   concisely the following:
			a. What is the purpose of the function?
			b. What is the nature of the functions return value (write "void" if
		   	   the function is of type void)
			c. What is the nature of each formal parameter?
			d. Pre-condition - what are the assumptions about the formal parameters?
	
	    Follow the online documentation style in the LinearSearch() example  
	    function definition given below.
*/


// DO NOT remove or edit the #if and #endif processor directives
#if 0
/*
	Purpose: determine if the search key is in the array or not using a linear
	         search algorithm 
	Returns: either the (a) index of the array where the key was found or
	         (b) a -1 to indicate that the key was not found
	@param : key is the search key
	@param : A is the name of the array containing the universe of values
	@param : n is the number of array elements to check
	Pre-condition: the parameters contain valid values
*/
int 
LinearSearch(key, int A[], int n)
{
	int i; // indexing variable

	// compare the search key with an element in the array
	for (i = 0; i < n; i++)
		if (key == A[i])  
			return i;  // this means that the key was found	

	return -1; // -1 means that the key not found
}
#endif


/*
    You may declare any typedef that you need below this comment.
*/




/*
    You may define any function that you need below this comment.
*/



int
main()
{
    /* Declare/define your own local variables. */
    
    /* Call the function(s) that you defined. */
       
    return 0;
}



