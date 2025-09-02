// Challenge #2: Representing and Storing the SHD using 1D and 2D Arrays, Input and Output (I/O) Redirection

#include <stdio.h>
#include <string.h>

int main() 
{
    char cStockSymbol[6]; 

    int nMaxRecord;

    // Read the stock symbol and number of records.
    scanf("%s", cStockSymbol);
    scanf("%d", &nMaxRecord);

    // Initializes the arrays to store date.
    char aDates[nMaxRecord][11];        // 1D array of strings for dates
    double aOHLC[nMaxRecord][4];        // 2D double array for OHLC values
    double aVolume[nMaxRecord];         // 1D double array for volume values

    int nRecordCounter = 0;

    while (nRecordCounter < nMaxRecord) {
        int nMonth, nDay, nYear;
        scanf("%d/%d/%d", &nMonth, &nDay, &nYear);

        // Ensures the year is formatted as four digits.
        if (nYear < 100) {   
            nYear += 2000;            
        }

        // Stores the date in MM/DD/YYYY format. 
        // '0' converts integers into character representation.
        // Month
        aDates[nRecordCounter][0] = '0' + (nMonth / 10);
        aDates[nRecordCounter][1] = '0' + (nMonth % 10);
        aDates[nRecordCounter][2] = '/';

        // Day
        aDates[nRecordCounter][3] = '0' + (nDay / 10);
        aDates[nRecordCounter][4] = '0' + (nDay % 10);
        aDates[nRecordCounter][5] = '/';

        // Year
        aDates[nRecordCounter][6] = '0' + ((nYear / 1000) % 10);
        aDates[nRecordCounter][7] = '0' + ((nYear / 100) % 10);
        aDates[nRecordCounter][8] = '0' + ((nYear / 10) % 10);
        aDates[nRecordCounter][9] = '0' + (nYear % 10);
        aDates[nRecordCounter][10] = '\0'; // Null terminator for string

        // Read OHLC values and trading volume.
        scanf("%lf %lf %lf %lf %lf",
                &aOHLC[nRecordCounter][0], &aOHLC[nRecordCounter][1],
                &aOHLC[nRecordCounter][2], &aOHLC[nRecordCounter][3],
                &aVolume[nRecordCounter]);

        nRecordCounter++;   // Moves on to the next record.
    }

    // Print stock symbol and number of records.
    printf("%s %d\n\n", cStockSymbol, nMaxRecord);

    // Print stored stock data with format.
    int nIndex;
    for (nIndex = 0; nIndex < nMaxRecord; nIndex++) {
        printf("%s\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\n",
                aDates[nIndex], aOHLC[nIndex][0], aOHLC[nIndex][1], 
                aOHLC[nIndex][2], aOHLC[nIndex][3], aVolume[nIndex]);   
    }

    return 0;
}