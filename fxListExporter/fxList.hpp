/*
fxList.hpp

Get List in double format.
*/


#ifndef _FXLIST_HPP_
#define _FXLIST_HPP_

#ifdef __cplusplus
  extern "C" {
#endif




// Get List col[row] in double format
// If no data in that grid, return NULL
double *GetList(int col, int row);




#ifdef __cplusplus
}
#endif

#endif