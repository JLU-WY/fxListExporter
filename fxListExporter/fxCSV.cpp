/*
fxCSV.cpp

Generate CSV line in string format.
*/


#ifdef __cplusplus
extern "C"
{
#endif




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fxCSV.hpp"
#include "fxList.hpp"


// Generate CSV line
char *GenerateCSVLine(int col_amount, int* col, int row, int line_end_type)
{
    char *line = (char *)malloc(sizeof(char) * (col_amount * 14 + 1));
    line[0] = '\0';
    
    
    int i;
    for (i = 0; i < col_amount; i++)
    {
        double *doubel_val = GetList(col[i], row); // double format value

        if (doubel_val) // data grid
        {
            char *string_val = (char *)malloc(sizeof(char) * 13); // string format value

            sprintf(string_val, "%G", *doubel_val);

            strcat(line, string_val);

            free(string_val);
        }
        else // no data grid
        {
            strcat(line, "N/A");
        }

        free(doubel_val);

        if (i == col_amount - 1) // last grid in that row
        {
            if (line_end_type == LINE_END_TYPE_1)
                strcat(line, "\n");
            else strcat(line, "$");
        }
        else 
        {
            strcat(line, ",");
        }
    }

    return line;
}




#ifdef __cplusplus
}
#endif