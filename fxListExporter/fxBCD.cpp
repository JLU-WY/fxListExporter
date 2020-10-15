/*
fxBCD.cpp

Convert BCD to/from double.
*/


#ifdef __cplusplus
extern "C"
{
#endif




#include <math.h>
#include <string.h>

#include "fxBCD.hpp"
#include "syscall.hpp"


// BCDtoInternal: convert TBCDvalue to TBCDInternal
typedef int (*sc_BCDtoInternal)(TBCDInternal *, TBCDvalue *);
const unsigned int sc500[] = {SCA, SCB, SCE, 0x500};
#define BCDtoInternal (*(sc_BCDtoInternal)sc500)


// Thanks Simon Lothar for this part.

//
TBCDvalue *TBCD::PValue()
{
    return FValue;
};

//
int TBCD::Get(TBCDvalue &value)
{
    int result = 0;
    memcpy(&value, &FValue, sizeof(TBCDvalue));
    return result;
};

//
int TBCD::Set(TBCDvalue &value)
{
    int result = 0;
    memcpy(&FValue, &value, sizeof(TBCDvalue));
    return result;
};

//
int TBCD::Set(double &value)
{
    int result = 0;
    double dwork;
    double dwork2;
    int iexponent;
    int i;
    memset(FValue, 0, sizeof(TBCDvalue));
    iexponent = 100;
    dwork = value;
    if (dwork < 0)
    {
        iexponent += 500;
        dwork = -dwork;
    };
    while (dwork >= 10)
    {
        iexponent += 1;
        dwork = dwork / 10;
    };
    while (dwork < 1)
    {
        iexponent -= 1;
        dwork = dwork * 10;
    };
    FValue[0].exponent = (iexponent / 100);
    iexponent = iexponent - (iexponent / 100) * 100;
    FValue[0].exponent <<= 4;
    FValue[0].exponent += (iexponent / 10);
    FValue[0].exponent <<= 4;
    iexponent = iexponent - (iexponent / 10) * 10;
    FValue[0].exponent += iexponent;

    dwork = modf(dwork, &dwork2) * 10;
    FValue[0].mantissa0 = floor(dwork2);
    for (i = 0; i < 7; i++)
    {
        dwork = modf(dwork, &dwork2) * 10;
        FValue[0].mantissa[i].hnibble = dwork2;
        dwork = modf(dwork, &dwork2) * 10;
        FValue[0].mantissa[i].lnibble = dwork2;
    }

    return result;
};

//
int TBCD::Get(double &value)
{
    int result = 0;
    int i;
    double factor = 1;
    TBCDInternal work;

    BCDtoInternal(&work, FValue); // syscall 0x500
    value = work.mantissa[0];
    for (i = 1; i < 15; i++)
    {
        factor /= 10;
        if (work.mantissa[i])
        {
            value += factor * work.mantissa[i];
        };
    };
    while (work.exponent++ < 0)
    {
        value /= 10;
    };
    while (--work.exponent > 0)
    {
        value *= 10;
    };
    value *= work.sign;

    return result;
};

//
int TBCD::SetError(int error)
{
    int result = (FValue[0].exponent & 0xF00) >> 4;
    FValue[0].exponent = (FValue[0].exponent & 0xFF) | (error << 4);
    return result;
};

//
int TBCD::GetError()
{
    int result = (FValue[0].exponent & 0xF00) >> 4;
    return result;
};

//
void TBCD::Swap()
{
    TBCDvalue work;
    FValue[0] = FValue[1];
    FValue[1] = work;
};




#ifdef __cplusplus
}
#endif