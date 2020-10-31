/*
fxList.cpp

Get List in double format.
*/


#ifdef __cplusplus
  extern "C" {
#endif




#include <stdlib.h>
#include <string.h>

#include "fxBCD.hpp"
#include "fxString.hpp"
#include "syscall.hpp"


// CalculateExpression: calculate an expression
typedef int (*sc_CalculateExpression)(char **, char[2], TBCDvalue *, int);
const unsigned int sc645[] = {SCA, SCB, SCE, 0x645};
#define CalculateExpression (*(sc_CalculateExpression)sc645)


// Get List col[row] in double format
// If no data in that grid, return NULL
double *GetList(int col, int row)
{
    TBCDvalue *bcd_value = (TBCDvalue *)malloc(sizeof(TBCDvalue)); // TBCDvalue format result
    double *double_value = (double *)malloc(sizeof(double)); // double value

    // Calculate expression: Listcol[row]
    
    char *expression = (char *)calloc(10, sizeof(char));
    char position[4]; // store col/row
    char bracket[2] = {0x5B, '\0'}; // store "[" and "]"

    // "List"
    expression[0] = 0x7F; // first part of "List"
    expression[1] = 0x51; // second part of "List"

    // col
    itoa(col, position);
    strcat(expression, position);

    // "["
    strcat(expression, bracket);

    // row
    itoa(row, position);
    strcat(expression, position);

    // "]"
    bracket[0] = 0x5D;
    strcat(expression, bracket);


    char opcode[2] = {1, 0};
    int mode = 1;
   

    // Get the result of List col[row] in BCD format
    // CalculateExpression() return 0 means no data in that grid
    if (!CalculateExpression(&expression, opcode, bcd_value, mode))
       return NULL;


    // Convert result to double format 

    TBCD *bcd = new TBCD;
    bcd->Set(*bcd_value);
    bcd->Get(*double_value);
    delete bcd;
    free(bcd_value);


    return double_value;
}




#ifdef __cplusplus
}
#endif