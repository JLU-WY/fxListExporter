/*
fxList.hpp

Get List in double format.
*/


#ifndef _FXLIST_HPP_
#define _FXLIST_HPP_

#ifdef __cplusplus
  extern "C" {
#endif


// itoa function
void itoa(int n, char s[]);


// Get List col[row] in double format
int GetList(double *double_value, int col, int row);




#ifdef __cplusplus
}
#endif

#endif