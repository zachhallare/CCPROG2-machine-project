/*
    Do not forget to encode the info for GROUP NUMBER, DATA SUBMITTED, name and section.
    A deduction of 0.5 point will be applied for not complying with this instruction!
    
    GROUP NUMBER (2 digits): 32
    DATE SUBMITTED         : Feb. 27, 2025

    LASTNAME1, FIRSTNAME1: Hallare, Zach Benedict              	SECTION1: S22B
    LASTNAME1, FIRSTNAME2: Campo, Benette Enzo                  SECTION2: S22B

    NOTE: encode ONLY your NAME and section if this code is for your own individual solution
          encode BOTH names and sections if this code is for your GROUP's final solution

    CCPROG2 MP Solution for Challenge #4 (C4)  

    Do the following:
	
	1. COMPILE your C source code with -Wall directive.
	
	       Example: CCPROG2> gcc -Wall 01-C4.c   
  
   	   where 01 is an example group number and C4 is the Challenge number.  
		  
	   You must replace 01 with your own group number!
  
	2. RUN the a.exe file in the command line with input and output (I/O) redirection.
	
	    	Example: CCPROG2> a < AC.txt > 01-C4-AC-OUTPUT.txt	   

            The text file 01-C4-AC-OUTPUT.txt will contain the actual output of your program.
       
        3. COMPARE your program's output with the accompanying C4-AC-EXPECTED.txt file using bbtest.exe.
    
	    	In case you do not have bbtest.exe, produce it first by compiling bbtest.c as shown below:
		
		 	Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe
		 	
	    Thereafter, run bbtest.exe with I/O redirection as shown below:
		
			Example: CCPROG2> bbtest C4-AC-EXPECTED.txt 01-C4-AC-OUTPUT.TXT > 01-C4-AC-BBTEST.txt
			
	    The output file 01-C4-AC-BBTEST.txt contains the results of the comparison.  If you see Differences = 0
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

#include "C4.h"  // read and understand the contents of this header file

/* Do NOT include other files. */ 

/* 
	HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or CAUSE POINT DEDUCTIONS!
	
	1. You are NOT allowed to use library functions that were NOT discussed 
	   in our class.
	2. You must apply arrays and strings in solving Challenge #4. 
	3. Do NOT use the following yet for this particular challenge:
	     a. struct data type
	     b. file processing functions such as fopen(), fclose(), etc.
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
	You may #define any constant that you need below this comment.
*/

/*
    You may declare any typedef that you need below this comment.
*/ 


/*
    Define the functions that you need below this comment.	
*/
/*
    Purpose: Reverses the order of dates, OHLC values, and trading volume data.
    @param aDates[]: Array of stock dates.
    @param aOHLC[][4]: 2D array containing OHLC (Open, High, Low, Close) prices.
    @param aVolume[]: Array containing trading volumes.
    @param nMaxRecord: Number of records to process.
*/
void reverseData(StrDate aDates[], double aOHLC[][4], double aVolume[], int nMaxRecord) {
    for (int i = 0; i < nMaxRecord / 2; i++) {
        // Swap dates
        StrDate tempDate;
        strcpy(tempDate, aDates[i]);
        strcpy(aDates[i], aDates[nMaxRecord - 1 - i]);
        strcpy(aDates[nMaxRecord - 1 - i], tempDate);

        // Swap OHLC
        for (int j = 0; j < 4; j++) {
            double temp = aOHLC[i][j];
            aOHLC[i][j] = aOHLC[nMaxRecord - 1 - i][j];
            aOHLC[nMaxRecord - 1 - i][j] = temp;
        }

        // Swap volume
        double tempVol = aVolume[i];
        aVolume[i] = aVolume[nMaxRecord - 1 - i];
        aVolume[nMaxRecord - 1 - i] = tempVol;
    }
}


/*
    Purpose: Reads Stock Historical Data (SHD) from standard input and stores it in arrays.
    @param aDates[]: Array to store stock dates in MM/DD/YYYY format.
    @param nMaxRecord: Maximum number of records to read.
    @param aOHLC[][4]: 2D array to store OHLC (Open, High, Low, Close) prices.
    @param aVolume[]: Array to store trading volumes.
    Pre-condition: Input must be formatted correctly (MM/DD/YY or MM/DD/YYYY followed by OHLC and volume values).
*/
void readSHD(StrDate aDates[], int nMaxRecord, double aOHLC[][4], double aVolume[])
{
	int nRecordCounter = 0;

    while (nRecordCounter < nMaxRecord) {
        int nMonth, nDay, nYear;
        scanf("%d/%d/%d", &nMonth, &nDay, &nYear);

        // Ensures the year is formatted as four digits.
        if (nYear < 100) {   
            nYear += 2000;            
        }

        //Stores the date in MM/DD/YYYY format. '0' converts integers into character representation.
        aDates[nRecordCounter][0] = '0' + (nMonth / 10);
        aDates[nRecordCounter][1] = '0' + (nMonth % 10);
        aDates[nRecordCounter][2] = '/';
        aDates[nRecordCounter][3] = '0' + (nDay / 10);
        aDates[nRecordCounter][4] = '0' + (nDay % 10);
        aDates[nRecordCounter][5] = '/';
        aDates[nRecordCounter][6] = '0' + ((nYear / 1000) % 10);
        aDates[nRecordCounter][7] = '0' + ((nYear / 100) % 10);
        aDates[nRecordCounter][8] = '0' + ((nYear / 10) % 10);
        aDates[nRecordCounter][9] = '0' + (nYear % 10);
        aDates[nRecordCounter][10] = '\0';  // Null terminator for string

        // Read OHLC values and trading volume.
        scanf("%lf %lf %lf %lf %lf",
                &aOHLC[nRecordCounter][0], &aOHLC[nRecordCounter][1],
                &aOHLC[nRecordCounter][2], &aOHLC[nRecordCounter][3],
                &aVolume[nRecordCounter]);

        nRecordCounter++;   // Moves on to the next record.
    }

	reverseData(aDates, aOHLC, aVolume, nMaxRecord);

}


/*
    Purpose: Computes the Simple Moving Average (SMA) over a specified period (m).
    @param m: The number of days in the moving average period.
    @param DateSMA[]: Array to store the corresponding dates for the computed SMA values.
    @param SMA[]: Array to store calculated SMA values.
    @param aDates[]: Array containing stock dates.
    @param aOHLC[][4]: 2D array storing OHLC prices (using closing prices for SMA calculation).
    @param nMaxRecord: The total number of available records.
    @returns: The number of SMA values computed.
    Pre-condition: m must be <= nMaxRecord, and OHLC data should be valid.
*/
int ComputeSMA(int m, StrDate DateSMA[], double SMA[], StrDate aDates[], double aOHLC[][4], int nMaxRecord)
{
	int count = 0;

	for(int i = m - 1; i < nMaxRecord; i++)
	{
		double sum = 0;

		for(int j = 0; j < m; j++)
		{
			sum += aOHLC[i - j][3];
		}

		SMA[count] = sum / m;

		strcpy(DateSMA[count], aDates[i]);

		count++;
	}

	return count;
 	
}

/*
	TO DO: Complete the body of the main() function.
*/

int
main()
{

    char cStockSymbol[6]; 
    int nMaxRecord;

    // Read the stock symbol and number of records.
    scanf("%s", cStockSymbol);
    scanf("%d", &nMaxRecord);

    // Initializes the arrays to store date.
    StrDate aDates[nMaxRecord];        // 1D array of strings for dates
    double aOHLC[nMaxRecord][4];        // 2D double array for OHLC values
    double aVolume[nMaxRecord];         // 1D double array for volume values

	/* TO DO: Declare your own local variables AFTER this comment.  You MUST declare and use variables 
	   for the following:
	   	1. a string for storing company symbol, example "AC" 
	   	2. an integer for storing the number of rows of stock historical data (in the case 
		   of AC.txt this value will store 1216)
	   	3. 1D array of string for storing the dates (assume that the date values in the SHD text file are 
		   are already formatted as "MM/DD/YYYY")
	   	4. 2D array of double values for storing the OHLC values
	   	5. 1D array of double for storing the volume
	*/
       

	/* Do NOT change the next four lines of variable declarations.  */
	int i, j, m;
	int count;
	StrDate DateSMA[MAX];  // 1D array of dates with corresponding SMA values
	double SMA[MAX];       // 1D array of SMA values 
	
	/* 
		Do NOT change the next line of array definition. View the C4.h header file 
		to see the values of the macros. 
	*/

	int test_cases[3] = { TEST_NDAYS1, TEST_NDAYS2, TEST_NDAYS3 };  
	    
	
	/* 
		TO DO: CALL the function that you defined above for reading the SHD.
	*/

	readSHD(aDates, nMaxRecord, aOHLC, aVolume); // fill-in the blank



	/* NOTE: The statements below should produce the required output. You are allowed
	         to change or edit ONLY those lines with blanks by filling-up the missing
			 information.
	         
	   Refer to the accompanying C4-AC-EXPECTED.txt to see the expected results using AC.txt as input file. 
	*/
		
	/* TO DO: fill up the blank to print the company symbol. */
	printf("%s\n\n", cStockSymbol);   
	
        /* The following lines are used to test the function you defined for computing 
	   the m-day SMA.  Three test values for m are used which correspond to the 
	   macros TEST_NDAYS1, TEST_NDAYS2, and TEST_NDAYS3. 
	*/ 
        for (i = 0; i < 3; i++) {  // for each test case
    	        m = test_cases[i];     // m is the number of days 
		printf("**TEST-%d-day-SMA**\n", m);
		
		/* TO DO: call the function that computes the m-day SMA. The function should
		   return an integer value to be stored in count. It must also accept as 1st
		   parameter the value of m, DateSMA array as 2nd parameter, and SMA array as
		   3rd parameter.  Supply the function name and the other parameters (aside
		   from the first 3 parameters stated above)) that you think you'll need to
		   accomplish the requirement. 
		*/
		count = ComputeSMA(m, DateSMA, SMA, aDates, aOHLC, nMaxRecord); 
			
		
	        /* The following will print the count value, the dates and SMA values. 
		   Again, refer to the accompanying C4-AC-EXPECTED.txt to see the expected
		   results using AC.txt as input file. 
		*/
		printf("count = %d\n", count);	
		for (j = 0; j < count; j++)
			printf("%3d  %s  %.2lf\n", j + 1, DateSMA[j], SMA[j]);
	
		printf("\n");
    	
	}
    
	return 0;
}
