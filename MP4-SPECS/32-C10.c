/*
    Do not forget to encode the info for GROUP NUMBER, DATE SUBMITTED, NAMES and SECTIONS.
    A deduction of 0.5 point will be applied for not complying with this instruction!
    
    GROUP NUMBER (2 digits): 32
    DATE SUBMITTED         : MAR. 30,2025

    LASTNAME1, FIRSTNAME1: CAMPO, BENETTE ENZO      SECTION1: S22B
    LASTNAME1, FIRSTNAME2: HALLARE, ZACH BENEDICT   SECTION2: S22B

    NOTE: encode ONLY your NAME and section if this code is for your own individual solution
          encode BOTH names and sections if this code is for your GROUP's final solution
	
	
    Make sure that you do the following:

    1. COMPILE your C source code with -Wall directive.
	
	       Example: CCPROG2> gcc -Wall 01-C10.c	   
  
       where 01 is an example group number and C10 is the Challenge number.
  
       You must replace 01 with your own group number!
  
    2. RUN the program's exe file in the command line. Unlike the previous challenges you should NOT use I/O redirection.
	   
	   		Example: CCPROG2> a

       Your program should produce two output text files named as:

	  a. GROUPNUMBER-PORTFOLIO.txt 
	  b. GROUPNUMBER-MYTEST.txt
	   
       based on the two function calls in the main() function. The output files should NOT be created inside
       the accompanying SHD folder; they should be in the same folder where you have your C source file.
	  
    3. COMPARE your program's GROUPNUMBER-PORTFOLIO.txt output file with the accompanying C10-EXPECTED.txt file 
       using bbtest.c.
    
       In case you do not have bbtest.exe, produce it first by compiling bbtest.c as shown below:
		
		 	Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe
		 	
       Thereafter, run bbtest.exe with I/O redirection as shown below:
		
			Example: CCPROG2> bbtest C10-EXPECTED.txt  01-PORTFOLIO.txt  >  01-C10-BBTEST.txt
			
       The output redirected file 01-C10-BBTEST.txt contains the results of the comparison.  If you see 
       Differences = 0 towards the end of the file, then it means that your program's output matches the
       expected output.  Otherwise, if you see a Differences value higher than 0, then there's a strong 
       probability that you either have a logical error in your program, or you did NOT follow the
       MP specifications (including the directions in this file).
		
       Debug your C source file, and redo the steps above until you get Differences = 0.
		
       Take note, however, that Differences = 0 does NOT necessarily mean that your solutions is 100% logically
       correct.  The bbtest.exe only tests if two files have the same contents.  It is not meant to test the logic
       of your C program.
	
    4. TEST your solution using the stock historical data for other companies.  Create your own portfolio
       text file and use them for testing. You'll have to figure out how to verify the correctness of your 
       program's output using your own test portfolio file.	
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
	TO DO: replace GROUPNUMBER in the #include below with your own group number.  For example if you are group 1,
	you should have #include "01-C6.h".  Group numbers from 1 to 9 should have a leading zero in the filename.
*/
#include "32-C6.h"

// Do NOT edit/delete the next #include directive
#include "numeric_date_helpers.c"  // read and understand the contents of this file

/* Do NOT include other files. */ 

/* 
	Do NOT define any constant in this file.  
        Do NOT declare any typedef that you need below this comment.
	You should encode #define and typedef declarations in your GROUPNUMBER-C6.h header file.
*/

/* 
	HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
	
	1. You are required to use TEXT FILE PROCESSING commands fopen(), fclose(), fscanf() and fprintf()
	   on top of previous topics in solving Challenge #10.
	2. You are required to implement and use a binary search algorithm for searching using buy date
	   as search key.	
	3. You are NOT allowed to use library functions that were NOT discussed in our class.
	4. Apply divide-and-conquer technique by segregating your program's logic into functions.
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
	
	    Follow the online documentation style in the LinearSearch() example function definition given below.
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

/* 
   TO DO: Define the functions that you need below this comment. 

          Remember that you need to implement the binary search algorithm with date 
          as search key.
*/

/*
    Function to read the historical stock data from a file.
    @param sFilename: the name of the input file
    @param pStockData: a pointer to the structure where the stock data will be stored
*/

void
readStockData(const char *sFilename, SData *pStockData)
{
	// Open the file in read mode (r) and check if it exists. If not, print an error message and exit.
	FILE *fp = fopen(sFilename, "r");
	if (fp == NULL)		
	{
    	fprintf(stderr, "ERROR: %s not found!\n", sFilename);
    	exit(1);
	}

    // Read the stock symbol and the number of rows from the file
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
                    nCount++;
                    if (nCount >= MAX_ROWS) break; 
                }

    pStockData->nNumRows = nCount;
    fclose(fp);
}

/*
    Function to find the closing price of a stock on a specific date using a binary search algorithm.
    @param stockData: a pointer to the structure containing the stock data
    @param sDate: the date for which the closing price needs to be found
    @return: the closing price of the stock on the specified date, or -1 if the date is not found
*/

double findClosePrice(SData *stockData, StrDate sDate)
{
	int left = 0, right = stockData->nNumRows - 1;
	int key = numeric_date(sDate); 

	while (left <= right)
	{
		int mid = left + ( right - left ) / 2;
		int MidDate = numeric_date(stockData->aStockRows[mid].cDate);

		if(key == MidDate)
		{
			return stockData->aStockRows[mid].fClose;
		}

		if (MidDate > key) // Binary search for descending order.
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}

	// Return -1 if the date is not found
	return -1;
}

void processPortfolio(const char *sPortfolioFilename, StrDate sReferenceDate)
{
	// Open the portfolio file in read mode (r) and check if it exists. If not, print an error message and exit.
	FILE *in_fp = fopen(sPortfolioFilename, "r");
	if (in_fp == NULL) {
        fprintf(stderr, "ERROR: %s not found!\n", sPortfolioFilename);
    	exit(1);
    }

	// Creates output file name
	SData stockData;
    char sOutputFilename[50];
	strcpy(sOutputFilename, "32-");
	strcat(sOutputFilename, sPortfolioFilename);

	// Open the output file in write mode (w) and check if it can be opened. If not, print an error message and exit.
	FILE *out_fp = fopen(sOutputFilename, "w");
    if (out_fp == NULL) {
        fprintf(stderr, "ERROR: Unable to write to %s\n", sOutputFilename);
        fclose(in_fp);
        exit(1);
    }

	// Print header to output file
	fprintf(out_fp, "PORTFOLIO PERFORMANCE AS OF %s\n\n", sReferenceDate);

	StrStock sSymbol;
	StrDate sBuyDate;
	int nShares;

	while(fscanf(in_fp, "%s %d %s", sSymbol, &nShares, sBuyDate) != EOF)
	{
		// Construct the stock data file name from the symbol to open inside SHD folder
		char sStockFilename[20];
        strcpy(sStockFilename, "SHD/");
        strcat(sStockFilename, sSymbol);
        strcat(sStockFilename, ".txt");

		// Read stock data from the file
		readStockData(sStockFilename, &stockData);

		// Find closing price on the reference date and calculate profit/loss and percentage.
		double dBuyPrice = findClosePrice(&stockData, sBuyDate);
        double dRefPrice = findClosePrice(&stockData, sReferenceDate);
    
        // Calculate the profit or loss
        double dProfitLoss = dRefPrice - dBuyPrice;
        double dPercentPL = (dProfitLoss / dBuyPrice) * 100;

        // Write the results to the output file
		fprintf(out_fp, "%-6s %5d  %10s %13.6f %13.6f %13.6f %13.6f\n", 
			sSymbol, nShares, sBuyDate, dBuyPrice, dRefPrice, dProfitLoss, dPercentPL);
	}

	fclose(in_fp);
    fclose(out_fp);
}

/*
     TO DO: Complete the body of the main() function.
*/

int
main()
{
	char portfolio_filename[100];
	char reference_date[11];
	// Do NOT declare/use other variables 
	

        /*
	   TO DO: Fill in the TWO blanks by supplying the name of the function that will process 
	   the contents of the portfolio text file based on the specified reference date.
	
	   DO NOT ADD/EDIT ANY OTHER CODES ASIDE FROM THOSE REQUIRED IN THE 2 BLANKS!!!
	*/


	// TEST #1: Call the function that will fullfill the C10 requirements using hardcoded actual parameters.
	processPortfolio("PORTFOLIO.txt", "12/27/2019");  

	
	// TEST #2: Call the function that will fullfill the C10 requirements using actual parameters specified via scanf()
	printf("Input the name of your test portfolio file: ");
	scanf("%s", portfolio_filename);   // example: MYTEST.txt or other files that you may want to use for testing
	printf("Input a reference date in MM/DD/YYYY format: ");
	scanf("%s", reference_date);  // example: 12/27/2019  or other dates you may want to use for testing	
	processPortfolio(portfolio_filename, reference_date);

        /* NOTE: In case the text file corresponding to portfolio_filename does not exist, the called function should 
           display an error message via

                fprintf(stderr, "ERROR: %s not found!\n", portfolio_filename);  

           Don't forget the exclamation mark in the error message string.
        */	

	return 0;
}
