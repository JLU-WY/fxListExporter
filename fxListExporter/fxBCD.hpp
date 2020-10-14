/*
fxBCD.hpp

Convert BCD to/from double.
*/


#ifndef _FXBCD_HPP_
#define _FXBCD_HPP_

#ifdef __cplusplus
  extern "C" {
#endif




// Thanks Simon Lothar for this part.

typedef struct{
  unsigned char hnibble:4;
  unsigned char lnibble:4;
} TBCDbyte;

typedef struct{
  unsigned short exponent:12;
  unsigned short mantissa0:4;
  TBCDbyte mantissa[7];
  char flags;
  short info;
} TBCDvalue;

typedef struct{
  int exponent;
  int sign;
  int unknown; 
  char mantissa[15];
} TBCDInternal;

class TBCD
{
public:
    TBCDvalue *PValue();
    int Get(TBCDvalue &value);
    int Set(TBCDvalue &value);
    int Set(double &value);
    int Get(double &value);
    int SetError(int error);
    int GetError();
    void Swap();

protected:
private:
    TBCDvalue FValue[2];
};




#ifdef __cplusplus
}
#endif

#endif