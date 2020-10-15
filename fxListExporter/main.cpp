#ifdef __cplusplus
  extern "C" {
#endif




#include <fxlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "fxList.hpp"
#include "syscall.hpp"




int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;


    Bdisp_AllClr_DDVRAM();

    locate(1, 1);
    Print((const unsigned char *)"fxListExporter demo");
    locate(1, 8);
    Print((const unsigned char *)"By Myth");
    locate(1, 3);
    Print((const unsigned char *)"List1[1]:");


    double *double_result = (double *)malloc(sizeof(double)); // double format result
    char *string_result = (char *)malloc(sizeof(char) * 22); // string format result

    
    if (GetList(double_result, 1, 1))
    {
        // Convert result to string format 

        sprintf(string_result, "%lf", *double_result);
        free(double_result);


        // Print string result

        locate(1, 4);
        Print((const unsigned char *)string_result);
    }
    else
    {
        locate(1, 4);
        Print((const unsigned char *)"NO VALUE!");
    }
    

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