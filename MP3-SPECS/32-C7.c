/*
    Do not forget to encode the info for GROUP NUMBER, DATA SUBMITTED, name and section.
    A deduction of 0.5 point will be applied for not complying with this instruction!
    
    GROUP NUMBER (2 digits): 32
    DATE SUBMITTED         : Mar. 20, 2025

    LASTNAME1, FIRSTNAME1: Hallare, Zach Benedict       		SECTION1: S22B
    LASTNAME1, FIRSTNAME2: Campo, Benette Enzo                  SECTION2: S22B

    NOTE: encode ONLY your NAME and section if this code is for your own individual solution
          encode BOTH names and sections if this code is for your GROUP's final solution

    CCPROG2 MP Solution for Challenge #7 (C7).
	
	Make sure that you do the following:
	
	1. COMPILE your C source code with -Wall directive.
	
	       Example: CCPROG2> gcc -Wall 32-C7.c
  
   	   where 01 is an example group number and C7 is the Challenge number.
  
  	   You must replace 01 with your own group number!
  
	2. RUN the a.exe file in the command line with input and output (I/O) redirection.
	
	       Example: CCPROG2> a < AC.txt > 32-C7-AC-OUTPUT.txt	   

           The text file 01-C7-AC-OUTPUT.txt will contain the actual output of your program using AC.txt stock data.
       
        3. COMPARE your program's output with the accompanying C7-AC-EXPECTED.txt file using bbtest.c.
    
	   In case you do not have bbtest.exe, produce it first by compiling bbtest.c as shown below:
		
		 	Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe
		 	
           Thereafter, run bbtest.exe with I/O redirection as shown below:
		
			Example: CCPROG2> bbtest C7-AC-EXPECTED.txt 32-C7-AC-OUTPUT.TXT > 32-C7-AC-BBTEST.txt
			
		The output redirected file 01-C7-AC-BBTEST.txt contains the results of the comparison.  If you see Differences = 0
		towards the end of the file, then it means that your program's output matches the expected output.
		Otherwise, if you see a Differences value higher than 0, then there's a strong probability that you
		either have a logical error in your program, or you did NOT follow the MP specifications (including
		the directions in this file).
		
		Debug your C source file, and redo the steps above until you get Differences = 0.
		
		Take note, however, that Differences = 0 does NOT necessarily mean that your solutions is 100% logically
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
	TO DO: replace GROUPNUMBER in the #include below with your own group number.  For example if you are group 1,
	you should have #include "01-C6.h".  Group numbers from 1 to 9 should have a leading zero in the filename.
*/
#include "32-C6.h"


/* 
    Do NOT define any constant in this file.  

    Do NOT declare any typedef that you need below this comment.

    You should encode your own #define and typedef declarations in your GROUPNUMBER-C6.h header file.
*/

// Do NOT edit/delete the next two #include directives.
#include "C7.h"                     // read and understand the contents of this file
#include "numeric_date_helpers.c"   // read and understand the contents of this file

/* Do NOT include other files. */ 


/* 
	HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
	
	1. You are NOT allowed to use library functions that were NOT discussed in our class.
	2. You must apply arrays of structures in solving Challenge #7. 
	3. Do NOT use the following yet for this particular challenge:
	    a. file processing functions such as fopen(), fclose(), etc.
	4. Apply divide-and-conquer technique by segregating your program's logic into functions.
	   A solution where all the logic are found only in the main() function 
	   will result to a 2-point deduction!
	5. Document your functions with SENSIBLE comments. Each function definition must
	   be PRECEDED by an online documentation (in the form of comments) describing
	   concisely the following:
			a. What is the purpose of the function?
			b. What is the nature of the functions return value (write "void" if
		   	   the function is of type void)
			c. What is the nature of each formal parameter?
			d. Pre-condition - what are the assumptions about the formal parameters?
	
	   Follow the online documentation style in the Search() example  
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
    TO DO: Implement a function that will read the stock historical data via scanf().  
	   The actual data will be supplied via input redirection.
		   
    Fill in the blanks.  The first missing item is the function name, and the second one 
    is the missing portion for the data type of formal parameter ptr_stock.  
    Take note that this function has ONE structure pointer formal parameter!
*/

/*
	Purpose: Reads stock market data from user input and stores it in the SData structure.
	Returns: Nothing.
	@param  : ptr_stock is a pointer to an SData structure where the stock data will be stored.
	Pre-condition: ptr_stock points to a valid SData structure.
*/
void
readStockData (SData *ptr_stock)  // do NOT change the parameter name
{
	int i;
	
	scanf("%s", ptr_stock->cStockSymbol);
	scanf("%d", &ptr_stock->nNumRows);

	// Read stock data for each row.
	for (i = 0; i < ptr_stock->nNumRows; i++) {
		scanf("%s %lf %lf %lf %lf %lf", ptr_stock->aStockRows[i].cDate, 
										&ptr_stock->aStockRows[i].fOpen, 
										&ptr_stock->aStockRows[i].fHigh,
										&ptr_stock->aStockRows[i].fLow,
										&ptr_stock->aStockRows[i].fClose,
										&ptr_stock->aStockRows[i].fVolume);
	}
}


/*
    TO DO: Implement a binary search function.
		   
    Fill in the blanks.  The  missing items are the return data type,
    the function name, and the formal parameters.
*/

/*
	Purpose: Perform a binary search to determine if the target date exists in the array 
	        of stock rows. If found, return its index; otherwise, return -1.
	Returns: Either the index of the array where the target date was found, or 
	        -1 to indicate that the target date was not found.
	@param : aStockRows is the array of stock data containing date values.
	@param : nNumRows is the total number of elements in the array.
	@param : targetDate is the date value being searched for.
	Pre-condition: The array aStockRows is sorted in descending order based on dates.
*/
int
binarySearch (SRow *aStockRows, int nNumRows, StrDate targetDate)  
{
	int nLeft = 0, nRight = nNumRows - 1, nMid;
	long int nKeyDate = numeric_date(targetDate);
	long int nMidDate;

    while (nLeft <= nRight) {
        nMid = nLeft + (nRight - nLeft) / 2;		// Calculate middle index.
		nMidDate = numeric_date(aStockRows[nMid].cDate);		// Get numeric date of the middle element.

		if (nMidDate == nKeyDate) {
            return nMid;	// Return if index is found.
        } 
		else if (nMidDate > nKeyDate) {
            nLeft = nMid + 1;		// Search the right half.
        } 
		else {
            nRight = nMid - 1;		// Search the left half.
        }
    }

    return -1;
}

/*
    TO DO: Implement the Trade() function.  Do NOT change the return type, 
	   function name, and formal parameter names.
    
    Fill in the blank by supplying the data type of the formal parameter 
    named as ptr_stock.	 
	
    Take note that this function has ONE structure pointer formal parameter!      
*/

/*
	Purpose: Determines the profit or loss from trading a stock by checking 
	        its buy and sell prices on given dates.
	Returns: Prints the trade details, including buy/sell prices, profit/loss, 
	        and percentage gain/loss. If dates are not found, prints an error message.
	@param : buy_date - The date when the stock was bought.
	@param : sell_date - The date when the stock was sold.
	@param : ptrStock - Pointer to the stock data structure containing stock records.
	Pre-condition: ptrStock is a valid pointer to a stock dataset, and buy_date and 
	                sell_date are formatted correctly.
*/
void 
Trade(StrDate buy_date, StrDate sell_date, SData *ptrStock)
{
	int nBuyIndex, nSellIndex;			// Indices of B&S dates in the stock.
	double fBuyPrice, fSellPrice;		// Closing prices on B&S dates.
	double fProfitLoss, fPercentPL;		// P&L and its percentage change.

	// Find the indices of the dates through binary search.
	nBuyIndex = binarySearch(ptrStock->aStockRows, ptrStock->nNumRows, buy_date);
	nSellIndex = binarySearch(ptrStock->aStockRows, ptrStock->nNumRows, sell_date);

	// Checks if both dates were found.
	if (nBuyIndex != -1 && nSellIndex != -1) {
		// Get the closing prices.
		fBuyPrice = ptrStock->aStockRows[nBuyIndex].fClose;
		fSellPrice = ptrStock->aStockRows[nSellIndex].fClose;

		// Compute profit loss and its percentage.
		fProfitLoss = fSellPrice - fBuyPrice;
		fPercentPL = (fProfitLoss / fBuyPrice) * 100;

		// Display the trade output.
		printf("BUY DATE %s FOUND IN INDEX %d!  BUY PRICE = %.2lf\n", buy_date, nBuyIndex, fBuyPrice);
		printf("SELL DATE %s FOUND IN INDEX %d!  SELL PRICE = %.2lf\n", sell_date, nSellIndex, fSellPrice);
		printf("P/L = %.2lf\n", fProfitLoss);
		printf("%%P/L = %.2lf\n", fPercentPL);
	}
	else {
		// Display error if any date is missing.
		if (nBuyIndex == -1 || nSellIndex == -1) {
			printf("BUY DATE %s NOT FOUND!\n", buy_date);
		}
		if (nSellIndex == -1) {
			printf("SELL DATE %s NOT FOUND!\n", sell_date);
		}
	}
}


/*
	TO DO: Complete the body of the main() function.
*/
int
main()
{	
	/* Do NOT change the next line of variable declaration. */
	int i;	
	
	/* Do NOT change the next two lines of array definition. View the C7.h header file to see the values of the macros. */
	StrDate buy_date[5]  = { TEST_BUYDATE1,  TEST_BUYDATE2,  TEST_BUYDATE3,  TEST_BUYDATE4,  TEST_BUYDATE5  };
	StrDate sell_date[5] = { TEST_SELLDATE1, TEST_SELLDATE2, TEST_SELLDATE3, TEST_SELLDATE4, TEST_SELLDATE5 };
  
	/* 
		TO DO: Declare your own local structure variable that will the store ALL the 
		SHD for ONE company read from an input text file.
	*/
	SData stock;  // supply the structure data type alias based on your C6 header file contents
	                   // the structure variable name should be stock -- don't change this!  
	
		
	/* NOTE: The statements below should produce the required output. You are allowed to change or edit
	         ONLY those lines with blanks by filling-up the missing information.
	
	*/   
 
 
	/* 
		TO DO: Fill in the blank by CALLing the function that you defined above for reading the stock historical data.
	*/
	readStockData(&stock); // do NOT change the &stock parameter, do NOT add other parameters
	
	/* TO DO: Fill in the blank to print the company symbol. */
	printf("%s\n", stock.cStockSymbol); 
	
	/* TO DO: Fill in the blank to print the count/number of rows of stock historical data. */
	printf("%d\n", stock.nNumRows); 
	printf("\n");
	

	/*
		DO NOT change any of the codes below.
	*/
	for (i = 0; i < 5; i++) {
		printf("**TEST-CASE-%d**\n", i + 1);       // there are 5 test cases
		Trade(buy_date[i], sell_date[i], &stock);  // you'll need to implement the Trade() function
		printf("\n");
	}
    
	/*         
	   Refer to the accompanying C7-AC-EXPECTED.TXT to see the expected results using AC.TXT as input file.
	*/

	return 0;
}
