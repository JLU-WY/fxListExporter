/*
fxInput.hpp

Input a string.
*/


#ifndef _FXINPUT_HPP_
#define _FXINPUT_HPP_

#ifdef __cplusplus
  extern "C" {
#endif




// Input Mode
#define NUM 0 // allow: 0~9
#define ALL_CHAR 1 // allow: 0~9 A~Z a~z .


// Input a string 
// Use SHFIT key to switch between upper and lower letter
// len is the max length of the str, without \0
// mode decides char allowed to input
char *InputString(int x, int y, int len, int mode);


// Draw a 5 num selector to control num_status.
// num_status is 0 or 1.
// num_amount > 5
void ControlNumStatus(int num_amount, int num_and_status[][2]);




#ifdef __cplusplus
}
#endif

#endif