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
#include "syscall.hpp"


// CalculateExpression: calculate an expression
typedef int (*sc_CalculateExpression)(char **, char[2], TBCDvalue *, int);
const unsigned int sc645[] = {SCA, SCB, SCE, 0x645};
#define CalculateExpression (*(sc_CalculateExpression)sc645)


// itoa function
void itoa(int n, char s[])
{
     int i, j, sign;
     char c;

     if ((sign = n) < 0)
         n = -n;
     i = 0;
     do {
         s[i++] = n % 10 + '0';
     } while ((n /= 10) > 0);
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}


// Get List col[row] in double format
int GetList(double *double_value, int col, int row)
{
    TBCDvalue *bcd_value = (TBCDvalue *)malloc(sizeof(TBCDvalue)); // TBCDvalue format result
    

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
    CalculateExpression(&expression, opcode, bcd_value, mode); 


    // Convert result to double format 

    TBCD *bcd = new TBCD;;
    bcd->Set(*bcd_value);
    bcd->Get(*double_value);
    delete bcd;
    free(bcd_value);


    return 1;
}




#ifdef __cplusplus
}
#endif