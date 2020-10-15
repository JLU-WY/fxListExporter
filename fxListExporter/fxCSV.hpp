/*
fxCSV.hpp

Generate CSV line in string format.
*/


#ifndef _FXCSV_HPP_
#define _FXCSV_HPP_

#ifdef __cplusplus
  extern "C" {
#endif




// use \n to end a line
#define LINE_END_TYPE_1 0

// use $ to end a line
#define LINE_END_TYPE_2 1


// Generate CSV line
char *GenerateCSVLine(int col_amount, int* col, int row, int line_end_type);




#ifdef __cplusplus
}
#endif

#endif