#ifdef __cplusplus
  extern "C" {
#endif




#include <fxlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "fxFile.hpp"
#include "fxInput.hpp"
#include "MonochromeLib.h"




int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;
    int save_method; // how to save the CSV file


    ML_clear_vram();

    // Print program info
    locate(1, 1);
    PrintRev((const unsigned char *)" fxListExporter v1.0  ");
    locate(1, 4);
    Print((const unsigned char *)"   Copyright 2020");
    locate(1, 5);
    Print((const unsigned char *)"        Myth");
     
    locate(1, 8);
    Print((const unsigned char *)"Press EXE to continue");

    // wait for EXE key
    do GetKey(&key);
    while (key != KEY_CTRL_EXE);


    ML_clear_vram();

    // Select columns

    locate(1, 2);
    Print((const unsigned char *)"Select columns:");

    int col_num_status[26][2] = 
    {
        {1, 0}, 
        {2, 0},
        {3, 0},
        {4, 0},
        {5, 0},
        {6, 0},
        {7, 0},
        {8, 0},
        {9, 0},
        {10, 0},
        {11, 0},
        {12, 0},
        {13, 0},
        {14, 0},
        {15, 0},
        {16, 0},
        {17, 0},
        {18, 0},
        {19, 0},
        {20, 0},
        {21, 0},
        {22, 0},
        {23, 0},
        {24, 0},
        {25, 0},
        {26, 0}
    };

    ControlNumStatus(26, col_num_status);

    int *col = (int*)calloc(26, sizeof(int));

    int col_amount = 0;
    for (int i = 0; i < 26; i++)
    {
        if (col_num_status[i][1])
        {
            col[col_amount] = col_num_status[i][0];
            col_amount++;
        }
    }


    ML_clear_vram();

    // Select rows

    locate(1, 2);
    Print((const unsigned char *)"Choose max row:");

    char *str_row = InputString(1, 4, 3, NUM);
    int max_row = atoi(str_row);
    free(str_row);


    ML_clear_vram();

    // Select save method

    locate(1, 2);
    Print((const unsigned char *)"Select save method:");
    locate(1, 4);
    Print((const unsigned char *)"[1]: Storage");
    locate(1, 5);
    Print((const unsigned char *)"[2]: SD Card");
    //locate(1, 6);
    //Print((const unsigned char *)"[3]: Show QR code");

    while (1)
    {
        GetKey(&key);

        if (key == KEY_CHAR_1)
        {
            save_method = FLASH;
            break;
        }
        else if (key == KEY_CHAR_2)
        {
            save_method = SDCARD;
            break;
        }
        //else if (key == KEY_CHAR_3)
    }


    ML_clear_vram();

    // if file already exists
    if (!FileGenerateCSV("LIST.CSV", save_method, col_amount, col, max_row))
    {
        locate(1, 2);
        Print((const unsigned char *)"File already exists!");
        locate(1, 8);
        Print((const unsigned char *)"Press F1 to overwrite.");

        // wait for F1 key
        do GetKey(&key);
        while (key != KEY_CTRL_F1);

        FileDelete("LIST.CSV", save_method);

        FileGenerateCSV("LIST.CSV", save_method, col_amount, col, max_row);
    }


    ML_clear_vram();
    locate(1, 2);
    Print((const unsigned char *)"Success!");

    
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