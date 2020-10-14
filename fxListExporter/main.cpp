#ifdef __cplusplus
  extern "C" {
#endif




#include <fxlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "fxBCD.hpp"
#include "syscall.hpp"


// CalculateExpression: calculate an expression
typedef int (*sc_CalculateExpression)(char **, char[2], TBCDvalue *, int);
const unsigned int sc645[] = {SCA, SCB, SCE, 0x645};
#define CalculateExpression (*(sc_CalculateExpression)sc645)


int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;


    Bdisp_AllClr_DDVRAM();

    locate(1, 1);
    Print((const unsigned char *)"fxListExporter demo");
    locate(1, 8);
    Print((const unsigned char *)"By Myth");


    TBCDvalue *bcd_result = (TBCDvalue *)malloc(sizeof(TBCDvalue)); // TBCDvalue format result
    double *double_result = (double *)malloc(sizeof(double)); // double format result
    char *string_result = (char *)malloc(sizeof(char) * 22); // string format result


    // Calculate expression: List1[1]
    
    char *expression = (char *)malloc(sizeof(char) * 7);
    expression[0] = 0x7F; // first part of "List"
    expression[1] = 0x51; // second part of "List"
    expression[2] = '1';
    expression[3] = 0x5B; // "["
    expression[4] = '1';
    expression[5] = 0x5D; // "]"
    expression[6] = '\0';

    char opcode[2] = {1, 0};
    int mode = 1;
   

    // Get the result of List1[1] in BCD format
    CalculateExpression(&expression, opcode, bcd_result, mode); 


    // Convert result to double format 

    TBCD *bcd = new TBCD;;
    bcd->Set(*bcd_result);
    bcd->Get(*double_result);
    delete bcd;
    free(bcd_result);


    // Convert result to string format 

    sprintf(string_result, "%lf", *double_result);
    free(double_result);


    // Print string result

    locate(1, 3);
    Print((const unsigned char *)"List1[1]:");

    locate(1, 4);
    Print((const unsigned char *)string_result);




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