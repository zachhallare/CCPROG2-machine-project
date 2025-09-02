/*
    Do not forget to encode the info for GROUP NUMBER, DATA SUBMITTED, name and section.
    A deduction of 0.5 point will be applied for not complying with this instruction!
    
    GROUP NUMBER (2 digits): 32
    DATE SUBMITTED         : Mar. 20, 2025

    LASTNAME1, FIRSTNAME1: Hallare, Zach Benedict               SECTION1: S22B
    LASTNAME1, FIRSTNAME2: Campo, Benette Enzo                  SECTION2: S22B

    NOTE: encode ONLY your NAME and section if this code is for your own individual solution
          encode BOTH names and sections if this code is for your GROUP's final solution

    CCPROG2 MP Solution for Challenge #6 (C6) -- header file.  	

    This file will be included in your source codes for Challenges #7 and #8.
    Make sure to test this header file with your C7 and C8 codes.
*/


/* 
   SO THAT YOU KNOW:  

   a. a header file has an extension of h.

   b. a header file would normally contain any or a combination of the following:
      - #include and #define directives, and other macro directives like #if and #endif in this source file
      - typedef declarations
      - struct declarations
      - function prototypes/declarations

   c. a header file SHOULD NOT contain
      - variable declarations
      - function definitions
*/


/* 
	Do NOT change the lines that contain #ifndef, #define and #endif processor directives.
*/
#ifndef C6_DEFINED 
    
   #define C6_DEFINED  (1)

   
/* 
    You may #define any number of constants that you need below this comment.
*/

#define MAX_ROWS (1500)

/*
    You may declare any typedef that you need below this comment.
*/
   
 
/*
	Do NOT change the next two typedef declarations.
	
	You should use StrDate alias for a string that represents date.
	You should use StrStock alias for a string that represents the stock code, for example: "AC", "GTCAP".
*/
typedef char StrDate[11]; 
typedef char StrStock[6];


/*
	TO DO: Declare your struct data type for representing and storing ONLY ONE row of stock historical data (SHD),
	i.e., date, OHLC and volume.  Again, it is for just one row (or one line of text), NOT for all 
	rows of stock data.
	
	Use sensible tag names and member names.  
	
	You are REQUIRED to write sensible inline comments to describe the puprose/use of each structure member.		 
*/  

// Contains individual stock data of the company.
struct StockRow {
    StrDate cDate;      // Date of the stock data.
    double fOpen;       // Opening price of the stock.
    double fHigh;       // Highest price of the stock.
    double fLow;        // Lowest price of the stock.
    double fClose;      // Closing price.
    double fVolume;     // Number of shares traded.
};

/*
	TO DO: Declare a typedef alias for the struct data type you declared above.
*/

typedef struct StockRow SRow;

/*
	TO DO: Declare your struct data type for representing and storing ALL values present in a text
	file which contains the stock data.
	
	This data structure will be used for storing the ff:		
        a. stock symbol
    	b. actual number of rows of data
        c. date, OHLC and Volume values for each row of data  -- you are REQUIRED to use the 
           struct data type or alias you declared above.
	
	Use sensible tag names and member names.  
	
	You are REQUIRED to write sensible inline comments to describe the purpose/use of each structure member.	 
*/  

// Contains all the stock values of the company.
struct StockData {
    StrStock cStockSymbol;              // Stock symbol.
    int nNumRows;                       // Number of stock data rows.
    SRow aStockRows[MAX_ROWS];     // Array of StockData structs.
};

/*
	TO DO: Declare a typedef alias for the struct data type you declared above.
*/

typedef struct StockData SData;

#endif
