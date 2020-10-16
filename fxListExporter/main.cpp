#ifdef __cplusplus
  extern "C" {
#endif




#include <fxlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "fxFile.hpp"


int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;


    Bdisp_AllClr_DDVRAM();

    locate(1, 1);
    Print((const unsigned char *)"fxListExporter demo");
    locate(1, 8);
    Print((const unsigned char *)"By Myth");
    locate(1, 3);
    Print((const unsigned char *)"Generate 3x3 CSV file");


    // Generate a 3x3 CSV file
    int col_amount = 3;
    int col[3] = {1, 2, 3};

    int row_amount = 3;
    int row[3] = {1, 2, 3};
    
    FileGenerateCSV("LIST.CSV", FLASH, col_amount, col, row_amount, row);


    GetKey(&key);

    return 1;
}




#pragma section _BR_Size
unsigned long BR_Size;
#pragma section

#pragma section _TOP

int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#ifdef __cplusplus
}
#endif

#pragma section