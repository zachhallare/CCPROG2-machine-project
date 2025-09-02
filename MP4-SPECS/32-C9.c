/*
    Do not forget to encode the info for GROUP NUMBER, DATE SUBMITTED, NAMES and SECTIONS.
    A deduction of 0.5 point will be applied for not complying with this instruction!
    
    GROUP NUMBER (2 digits): 32
    DATE SUBMITTED         : MAR. 30, 2025

    LASTNAME1, FIRSTNAME1: CAMPO, BENETTE ENZO      SECTION1: S22B
    LASTNAME1, FIRSTNAME2: HALLARE, ZACH BENEDICT   SECTION2: S22B

    NOTE: encode ONLY your NAME and section if this code is for your own individual solution
          encode BOTH names and sections if this code is for your GROUP's final solution
	
    Make sure that you do the following:
	
    1. COMPILE your C source code with -Wall directive.
	
	       Example: CCPROG2> gcc -Wall 32-C9.c
  
       where 01 is an example group number and C9 is the Challenge number.
  
       You must replace 01 with your own group number!
  
    2. RUN the program's exe file in the command line. Unlike the previous challenges you should NOT use I/O redirection.
	   
	   		Example: CCPROG2> a	   

       The input data should be read from the text files stored in the accompanying folder named as SHD.

       The output file should NOT be created inside the accompanying SHD folder; it should be
       in the same folder where you have your C source file.
	  
       For the 1st test  function call in main(), a new output text file named as 01-AC.txt will be 
       produced after the program execution. 

       For the 2nd test function call, an error message "XYZ data file not found." will be 
       displayed on the standard error device (i.e., display screen) via fprintf(stderr, _____).

       Lastly, the 3rd test function call will perform the required task based on a symbol input by the user.

    3. COMPARE your program's output text file (using AC.txt as input data) with the accompanying C9-AC-EXPECTED.txt 
       file using bbtest.c.
    
       In case you do not have bbtest.exe, produce it first by compiling bbtest.c as shown below:
		
		 	Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe
		 	
       Thereafter, run bbtest.exe with I/O redirection as shown below:
		
			Example: CCPROG2> bbtest C9-AC-EXPECTED.txt 32-AC.txt > 32-C9-BBTEST.txt
			
       The output redirected file 01-C9-BBTEST.txt contains the results of the comparison.  If you see 
       Differences = 0 towards the end of the file, then it means that your program's output matches the
       expected output.  Otherwise, if you see a Differences value higher than 0, then there's a strong 
       probability that you either have a logical error in your program, or you did NOT follow the
       MP specifications (including the directions in this file).
		
       Debug your C source file, and redo the steps above until you get Differences = 0.
		
       Take note, however, that Differences = 0 does NOT necessarily mean that your solution is 100% logically
       correct.  The bbtest.exe only tests if two files have the same contents.  It is not meant to test the logic
       of your C program.
	
    4. TEST your solution using the stock historical data for other companies other than AC.txt.  Note that there
       are no expected output files provided for other companies.  You'll have to figure out how to verify the 
       correctness of your program's output on your own. 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
	For C9: you have the option to use or not to use the structure data type you declared in your
	        C6 header file.  If you decide to use it, then uncomment Line 80, and replace 
	        GROUPNUMBER in the #include with your own group number.  For example if you are group 1,
	        you should have #include "01-C6.h".  Group numbers from 1 to 9 should have a leading zero in
		the filename.
*/
#include "32-C6.h"

// Do NOT edit/delete the next #include directive
#include "numeric_date_helpers.c"  // read and understand the contents of this file

/* Do NOT include other files. */ 

/* 
	HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
	
	1. You are required to use TEXT FILE PROCESSING commands fopen(), fclose(), fscanf() and fprintf()
	   on top of previous topics in solving Challenge #9.	
	2. You are NOT allowed to use library functions that were NOT discussed in our class.
	3. Apply divide-and-conquer technique by segregating your program's logic into functions.
	   A solution where all the logic are found only in the main() function 
	   will result to a 2-point deduction!
	4. Document your functions with SENSIBLE comments. Each function definition must
	   be PRECEDED by an online documentation (in the form of comments) describing
	   concisely the following:
		a. What is the purpose of the function?
		b. What is the nature of the functions return value (write "void" if
		   the function is of type void)
		c. What is the nature of each formal parameter?
		d. Pre-condition - what are the assumptions about the formal parameters?
	
	   Follow the online documentation style in the Search() example function definition given below.
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
Search(key, int A[], int n)
{
	int i; // indexing variable

	// compare the search key with an element in the array
	for (i = 0; i < n; i++)
		if (key == A[i])  
			return i;  // this means that the key was found	

	return -1; // -1 means that the key not found
}
#endif


/* TO DO: define the functions that you need below this comment. */

/*
    Purpose: Converts a numeric date string (YYYYMMDD) to a formatted date string (YYYY-MMM-DD).
    Returns: void (modifies sDate in place).
    @param sDate: The character array containing the numeric date string.
    Pre-condition: sDate is in YYYYMMDD format and has enough space for the new format.
*/
void
convertDataFormat(char *sDate)
{
	char aMonths[12][4] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", 
							"JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

    int nMonthIndex = (sDate[0] - '0') * 10 + (sDate[1] - '0');         // Convert MM to int
    char sDay[3] = {sDate[3], sDate[4], '\0'};                          // Copy DD
    char sYear[5] = { sDate[6], sDate[7], sDate[8], sDate[9], '\0' };    // Copy YYYY

	// Construct final formatted date string.
	strcpy(sDate, sYear);
	strcat(sDate, "-");
	strcat(sDate, aMonths[nMonthIndex - 1]);
	strcat(sDate, "-");
	strcat(sDate, sDay);
}


/*
    Purpose: Reads stock data from a given file and stores it in an SData structure.
    Returns: Number of rows read, or -1 if the file does not exist.
    @param sFilename: The name of the file to read from.
    @param pStockData: Pointer to the SData structure where data will be stored.
    Pre-condition: sFilename is a valid file name, and pStockData points to a valid structure.
*/
int
readStockData(const char *sFilename, SData *pStockData)
{
	FILE *fp = fopen(sFilename, "r");	// Open the file for reading.
	if (fp == NULL)		// Checks if file not found.
	{
    	fprintf(stderr, "ERROR: %s not found!\n", sFilename + 4);      // sFilename + 4 so it only shows the textfile.
    	return -1;
	}

    fscanf(fp, "%s %d", pStockData->cStockSymbol, &pStockData->nNumRows);

    int nCount = 0;
    while (fscanf(fp, "%s %lf %lf %lf %lf %lf", 
                pStockData->aStockRows[nCount].cDate, 
                &pStockData->aStockRows[nCount].fOpen, 
                &pStockData->aStockRows[nCount].fHigh, 
                &pStockData->aStockRows[nCount].fLow, 
                &pStockData->aStockRows[nCount].fClose, 
                &pStockData->aStockRows[nCount].fVolume) != EOF)
                {
                    convertDataFormat(pStockData->aStockRows[nCount].cDate);
                    nCount++;

                    if (nCount > MAX_ROWS) 
                    {
                        break;
                    }
                }
    
    pStockData->nNumRows = nCount;
    fclose(fp);
    return nCount;
}


/*
    Purpose: Reverses the order of stock rows in an SData structure.
    Returns: void (modifies pStockData in place).
    @param pStockData: Pointer to the SData structure containing stock data.
    Pre-condition: pStockData contains valid data.
*/
void
reverseStockRows(SData *pStockData)
{
	int start = 0;
	int end = pStockData->nNumRows - 1;

	// Swap elements from start to end until middle is reached.
	while (start < end)
	{
		SRow temp = pStockData->aStockRows[start];
		pStockData->aStockRows[start] = pStockData->aStockRows[end];
		pStockData->aStockRows[end] = temp;

		start++;
		end--;
	}
}


/*
    Purpose: Writes stock data from an SData structure to a file.
    Returns: void.
    @param sFilename: The name of the file to write to.
    @param pStockData: Pointer to the SData structure containing stock data.
    Pre-condition: sFilename is valid and writable, pStockData contains valid data.
*/
void writeStockData(const char *sFilename, SData *pStockData) {
	FILE *fp = fopen(sFilename, "w");	// Open file for writing. 
	if (fp == NULL) {	// Checks if file not found.
		fprintf(stderr, "ERROR: Unable to write to %s\n", sFilename);
		exit(1);
	}
	
	// Write stock symbol and number of rows at the 1st row.
	fprintf(fp, "%s %d\n\n", pStockData->cStockSymbol, pStockData->nNumRows);

	// Write each stock row's data to the file.
	for (int i = 0; i < pStockData->nNumRows; i++) {
		fprintf(fp, "%s  %.2f  %.2f  %.2f  %.2f  %.2f\n",
				pStockData->aStockRows[i].cDate, 
				pStockData->aStockRows[i].fOpen, 
				pStockData->aStockRows[i].fHigh,
				pStockData->aStockRows[i].fLow, 
				pStockData->aStockRows[i].fClose, 
				pStockData->aStockRows[i].fVolume);
	}

	fclose(fp);
}

/*
    Purpose: The "Semi-Main" function. Reads, reverses, and writes stock data based the given.
    Returns: void.
    @param sSymbol: The stock symbol used to identify the input and output files.
    Pre-condition: sSymbol is a valid stock symbol string.
*/
void
processStockData(const char *sSymbol)
{
	SData stockData;
	strcpy(stockData.cStockSymbol, sSymbol);
	char sInputFilename[20], sOutputFilename[20];
	
	// Construct the input filename.
	strcpy(sInputFilename, "SHD/");
	strcat(sInputFilename, sSymbol);
	strcat(sInputFilename, ".txt");

	// Construct the output filename.
	strcpy(sOutputFilename, "32-");
	strcat(sOutputFilename, sSymbol);
	strcat(sOutputFilename, ".txt");

	// Read stock data from the input file.
	if (readStockData(sInputFilename, &stockData) == -1) {
        exit(1);    
    };

	// Reverse the order of stock data to ensure chronological order.
	reverseStockRows(&stockData);

	// Write the modified stock data to the output file.
	writeStockData(sOutputFilename, &stockData);

	// Confirmation message regarding the output.
	printf("Output written to %s\n", sOutputFilename);
}





/*
   main() function for testing student's solution.
*/
int
main()
{
        char symbol[8];
	// Do NOT declare/use other local variables.

        /*
	   Fill in the blank by supplying the missing name of the function that will accomplish the following:

	   1. Read the contents of the input text file containing the stock historical data for the company 
	      corresponding to the symbol specified as actual parameter. For example, if the actual parameter
              is "AC", then the function should read ALL the contents of the file "AC.txt" stored in the SHD folder.

	   2. Write the contents of the output text file which contains basically the same set of values as the input
	      text file but with TWO differences:
                a. the date values are formatted as "YYYY-AA-DD" (for example, "2021-OCT-27") where "AAA" represents the
                   first 3 characters of the month in word (in capital letters), i.e., "JAN", "FEB", ..., "NOV", "DEC".
                b. the rows of data are in listed in CHRONOLOGICAL order starting from the oldest date to the most recent date.
	 
	   The name of the output text file should be GROUPNUMBER-SYMBOL.txt where SYMBOL is the stock's symbol. For 
	   example, if your group number is 1, and the stock symbol is AC, then the output file should be named
	   as 01-AC.txt.  

           DO NOT ADD/EDIT ANY OTHER CODES ASIDE FROM THOSE REQUIRED IN THE 3 BLANKS!!!
        */   

	
        // #1: Call the function that will do fullfill the C9 requirements.  
        //     Fill in the missing function name with "AC" as actual parameter value.
	processStockData("AC");   // TEST #1: AC -- test the solution for an existing stock symbol AC.txt.
	                             // Your program should produce the output text file named GROUPNUMBER-AC.txt 
                                     // located in the same folder as your C source file.

        // #2. Do a second function call, this time with "XYZ" as the actual parameter value.
	processStockData("XYZ");  // TEST #2: XYZ -- test the solution for a NON-existent stock symbol.
	                             // Since there's no company with XYZ as stock symbol, your solution should
				     // display an error message on the standard error device.  The EXACT error message should be:
	                             //     "ERROR: XYZ.TXT not found!"  (don't forget the exclamation mark)
                                     // NOTE: You must use fprintf(stderr, ____) to display the error message.

	// #3. Do a third function call, this time with a company symbol input by the user.
	printf("Input the stock symbol: ");
	scanf("%s", symbol);  // symbol may or may not exist (ex. "MPI", "GTCAP", "ZZZ", etc...) 
	processStockData(symbol); // TEST #3: -- test using a symbol input by the user

	return 0;
}
