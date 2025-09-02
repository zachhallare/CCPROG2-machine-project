/* 

    C8.h
    Header file for Challenge #8
    
    You are NOT allowed to change the contents of this file.

*/


#define MAX_SIGNAL_SIZE (1220)

// The values of TEST_NDAYS1 to TEST_NDAYS2 correspond to the m in 
// the m-day Simple Moving Average computation.
#define TEST_NDAYS1 (9)
#define TEST_NDAYS2 (20)
#define TEST_NDAYS3 (50)
#define TEST_NDAYS4 (200)


/*
   structure type declaration for buy/sell signal based on short term MA and long term MA
*/
struct signalTag {
	StrDate date;          // format is "MM/DD/YYYY"        
	double short_term_MA;  // short term Moving Average 
	double long_term_MA;   // long term Moving Average
	char signal;           // signal is either a 'B' for BUY or an 'S' for SELL	
};

typedef struct signalTag signalType;

struct indicatorTag {
	StrStock symbol;   // stock symbol, for ex. "AC", "MPI", "GTCAP"
	int mst;           // m short term number of days, ex. mst = 50 (for 50-day MA)
	int mlt;           // m long term number of days, ex. mlt = 200 (for 200-day MA) 
	int count;         // actual number of elements in the SIGNAL array
	signalType SIGNAL[MAX_SIGNAL_SIZE];	
};

typedef struct indicatorTag indicatorType;

