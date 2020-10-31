/*
fxInput.cpp

Input a string.
*/


#ifdef __cplusplus
  extern "C" {
#endif




#include <fxlib.h>
#include <stdlib.h>
#include <string.h>

#include "fxInput.hpp"
#include "fxString.hpp"
#include "MonochromeLib.h"


// Upper or lower letter
#define LOWER_CASE 0
#define UPPER_CASE 1


// Input a string 
// Use SHFIT key to switch between upper and lower letter
// len is the max length of the str, without \0
// mode decides char allowed to input
char *InputString(int x, int y, int len, int mode)
{
    unsigned int key;
    int place = 0; // control the place of the cursor
    int alpha_status = UPPER_CASE; // upper letter or lower letter

    char *str = (char *)calloc(len + 1, sizeof(char));


    while (key != KEY_CTRL_EXE) // when EXE key down, end the input process
    {
        // print the cursor
        locate(x + place, y);
        Print((unsigned char *)"_");
        
        GetKey(&key); // get the current key

        switch (key)
        {
        case KEY_CTRL_AC: // when AC key down, clear the input
        {
            locate(x, y);
            Print((unsigned char *)"                     "); // clear that line in screen
            memset(str, '\0', len); // clear str
            place = 0; // move the cursor to the beginning
        }
        break;

        case KEY_CTRL_DEL: // when DEL key down, delete one char
        {
            if (place == 0) // if the cursor is already in the beginning, skip
                continue;

            locate(x + place - 1, y);
            Print((unsigned char *)"  "); // clear the deleted char
            str[place - 1] = '\0'; // put \0 in that place
            place--; // move the cursor backward 
        }
        break;

        default:
        {
            if (place == len) // if str is filled, skip
                continue;

            switch (key)
            {
            case KEY_CHAR_0:
            {
                locate(x + place, y);
                Print((unsigned char *)"0");
                str[place] = '0';
                place++; // move the cursor forward
            }
            break;

            case KEY_CHAR_1:
            {
                locate(x + place, y);
                Print((unsigned char *)"1");
                str[place] = '1';
                place++;
            }
            break;

            case KEY_CHAR_2:
            {
                locate(x + place, y);
                Print((unsigned char *)"2");
                str[place] = '2';
                place++;
            }
            break;

            case KEY_CHAR_3:
            {
                locate(x + place, y);
                Print((unsigned char *)"3");
                str[place] = '3';
                place++;
            }
            break;

            case KEY_CHAR_4:
            {
                locate(x + place, y);
                Print((unsigned char *)"4");
                str[place] = '4';
                place++;
            }
            break;

            case KEY_CHAR_5:
            {
                locate(x + place, y);
                Print((unsigned char *)"5");
                str[place] = '5';
                place++;
            }
            break;

            case KEY_CHAR_6:
            {
                locate(x + place, y);
                Print((unsigned char *)"6");
                str[place] = '6';
                place++;
            }
            break;

            case KEY_CHAR_7:
            {
                locate(x + place, y);
                Print((unsigned char *)"7");
                str[place] = '7';
                place++;
            }
            break;

            case KEY_CHAR_8:
            {
                locate(x + place, y);
                Print((unsigned char *)"8");
                str[place] = '8';
                place++;
            }
            break;

            case KEY_CHAR_9:
            {
                locate(x + place, y);
                Print((unsigned char *)"9");
                str[place] = '9';
                place++;
            }
            break;

            default:
            {
                if (mode == NUM) // if mode is NUM, skip
                    continue;

                switch (key)
                {
                case KEY_CTRL_SHIFT: // when SHIFT key down, change the alpha_status
                {
                    alpha_status = !alpha_status;
                }
                break;

                case KEY_CHAR_A:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"A");
                        str[place] = 'A';
                    }
                    else
                    {
                        Print((unsigned char *)"a");
                        str[place] = 'a';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_B:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"B");
                        str[place] = 'B';
                    }
                    else
                    {
                        Print((unsigned char *)"b");
                        str[place] = 'b';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_C:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"C");
                        str[place] = 'C';
                    }
                    else
                    {
                        Print((unsigned char *)"c");
                        str[place] = 'c';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_D:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"D");
                        str[place] = 'D';
                    }
                    else
                    {
                        Print((unsigned char *)"d");
                        str[place] = 'd';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_E:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"E");
                        str[place] = 'E';
                    }
                    else
                    {
                        Print((unsigned char *)"e");
                        str[place] = 'e';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_F:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"F");
                        str[place] = 'F';
                    }
                    else
                    {
                        Print((unsigned char *)"f");
                        str[place] = 'f';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_G:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"G");
                        str[place] = 'G';
                    }
                    else
                    {
                        Print((unsigned char *)"g");
                        str[place] = 'g';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_H:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"H");
                        str[place] = 'H';
                    }
                    else
                    {
                        Print((unsigned char *)"h");
                        str[place] = 'h';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_I:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"I");
                        str[place] = 'I';
                    }
                    else
                    {
                        Print((unsigned char *)"i");
                        str[place] = 'i';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_J:
                {

                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"J");
                        str[place] = 'J';
                    }
                    else
                    {
                        Print((unsigned char *)"j");
                        str[place] = 'j';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_K:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"K");
                        str[place] = 'K';
                    }
                    else
                    {
                        Print((unsigned char *)"k");
                        str[place] = 'k';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_L:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"L");
                        str[place] = 'L';
                    }
                    else
                    {
                        Print((unsigned char *)"l");
                        str[place] = 'l';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_M:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"M");
                        str[place] = 'M';
                    }
                    else
                    {
                        Print((unsigned char *)"m");
                        str[place] = 'm';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_N:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"N");
                        str[place] = 'N';
                    }
                    else
                    {
                        Print((unsigned char *)"n");
                        str[place] = 'n';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_O:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"O");
                        str[place] = 'O';
                    }
                    else
                    {
                        Print((unsigned char *)"o");
                        str[place] = 'o';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_P:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"P");
                        str[place] = 'P';
                    }
                    else
                    {
                        Print((unsigned char *)"p");
                        str[place] = 'p';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_Q:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"Q");
                        str[place] = 'Q';
                    }
                    else
                    {
                        Print((unsigned char *)"q");
                        str[place] = 'q';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_R:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"R");
                        str[place] = 'R';
                    }
                    else
                    {
                        Print((unsigned char *)"r");
                        str[place] = 'r';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_S:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"S");
                        str[place] = 'S';
                    }
                    else
                    {
                        Print((unsigned char *)"s");
                        str[place] = 's';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_T:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"T");
                        str[place] = 'T';
                    }
                    else
                    {
                        Print((unsigned char *)"t");
                        str[place] = 't';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_U:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"U");
                        str[place] = 'U';
                    }
                    else
                    {
                        Print((unsigned char *)"u");
                        str[place] = 'u';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_V:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"V");
                        str[place] = 'V';
                    }
                    else
                    {
                        Print((unsigned char *)"v");
                        str[place] = 'v';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_W:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"W");
                        str[place] = 'W';
                    }
                    else
                    {
                        Print((unsigned char *)"w");
                        str[place] = 'w';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_X:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"X");
                        str[place] = 'X';
                    }
                    else
                    {
                        Print((unsigned char *)"x");
                        str[place] = 'x';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_Y:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"Y");
                        str[place] = 'Y';
                    }
                    else
                    {
                        Print((unsigned char *)"y");
                        str[place] = 'y';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_Z:
                {
                    locate(x + place, y);
                    if (alpha_status)
                    {
                        Print((unsigned char *)"Z");
                        str[place] = 'Z';
                    }
                    else
                    {
                        Print((unsigned char *)"z");
                        str[place] = 'z';
                    }
                    place++;
                }
                break;

                case KEY_CHAR_DP:
                {
                    locate(x + place, y);
                    Print((unsigned char *)".");
                    str[place] = '.';
                    place++;
                }
                }
            }
            }
        }
        }
    }


    if (!place) // if nothing input, return NULL
    {
        free(str);

        return NULL;
    }


    str[place] = '\0';

    return str;
}


#define BUTTON_HEIGHT 11
#define BUTTON_WIDTH 19

#define BUTTON_NORM 0
#define BUTTON_REV 1

// Draw 6 buttons at the bottom of the screen, with 5 numbers and one control symbol
// num_and_status = {{1, BUTTON_NORM}, {2, BUTTON_REV}, ...}
// Print 1 at the first button; Print 2 at the second button in reverse color; ... Print > at the sixth button.
// 1 <= num <= 99
void DrawNumButton(int **num_and_status)
{
    int x1 = 2, y1 = 53; // coordinate of the upper left point of the first button
    int x2 = x1 + BUTTON_WIDTH - 1, y2 =  y1 + BUTTON_HEIGHT - 1; // coordinate of the bottom right point of the first button

    int x; // x coordinate of the first num
    int x_one = 8; // x = x_one if the first num is one-digital
    int x_two = 5; // x = x_two if the first num is two-digital
    int y = 55; // y coordinate of the first num
    

    // print the num
    
    char *str_num = (char *)calloc(3, sizeof(char));

    for (int i = 0; i < 5; i++)
    {
        // check the digital of num
        if (num_and_status[i][0] < 10)
            x = x_one;
        else x = x_two;
        
        itoa(num_and_status[i][0], str_num);
        
        // check whether to reserve color
        if (num_and_status[i][1] == BUTTON_NORM)
        {
            ML_rectangle(x1, y1, x2, y2, 1, ML_BLACK, ML_WHITE);
            PrintXY(x, y, (const unsigned char*)str_num, 0);
        }
        else
        {
            ML_rectangle(x1, y1, x2, y2, 1, ML_BLACK, ML_BLACK);
            PrintXY(x, y, (const unsigned char*)str_num, 1);
        }
        
        // move x coordinate
        x1 += BUTTON_WIDTH + 2;
        x2 += BUTTON_WIDTH + 2;
        x_one += BUTTON_WIDTH + 2;
        x_two += BUTTON_WIDTH + 2;
    }

    free(str_num);

    // draw the symbol

    unsigned char symbol[3] = {0xE6, 0x9B, 0}; // > symbol

    ML_rectangle(x1, y1, x2, y2, 1, ML_BLACK, ML_BLACK);
    PrintXY(x_one, y, (const unsigned char*)symbol, 1);
}


// Get numbers from the num_and_status array
// num_and_status = {{1, 0}, {2, 0}, ..., {26, 0}}
// GetCurrnetNumStatus(24, 5, 26, num_and_status)
// Your will get {{24, 0}, {25, 0}, {26, 0}, {1, 0}, {2, 0}}
// start_place <= num_amount
int** GetCurrnetNumStatus(int start_place, int get_length, int num_amount, int num_and_status[][2])
{
    // collect memory for current_num_status
    int** current_num_status = (int**)calloc(get_length, sizeof(int));
    for (int i = 0; i < get_length; i++)
    {
        current_num_status[i] = (int*)calloc(2, sizeof(int));
    }


    if (start_place <= num_amount - get_length + 1)
    {
        for (int i = 0; i < get_length; i++)
        {
            current_num_status[i][0] = num_and_status[start_place + i - 1][0];
            current_num_status[i][1] = num_and_status[start_place + i - 1][1];
        }
    }
    else
    {
        for (int i = 0; i < num_amount - start_place + 1; i++)
        {
            current_num_status[i][0] = num_and_status[start_place + i - 1][0];
            current_num_status[i][1] = num_and_status[start_place + i - 1][1];
        }

        for (int i = num_amount - start_place + 1; i < get_length; i++)
        {
            current_num_status[i][0] = num_and_status[start_place + i - num_amount - 1][0];
            current_num_status[i][1] = num_and_status[start_place + i - num_amount - 1][1];
        }
    }

    return current_num_status;
}


// Get numbers and status to the num_and_status array
void PutCurrnetNumStatus(int **current_num_status, int start_place, int get_length, int num_amount, int num_and_status[][2])
{
    if (start_place <= num_amount - get_length + 1)
    {
        for (int i = 0; i < get_length; i++)
        {
            num_and_status[start_place + i - 1][0] = current_num_status[i][0];
            num_and_status[start_place + i - 1][1] = current_num_status[i][1];
        }
    }
    else
    {
        for (int i = 0; i < num_amount - start_place + 1; i++)
        {
            num_and_status[start_place + i - 1][0] = current_num_status[i][0];
            num_and_status[start_place + i - 1][1] = current_num_status[i][1];
        }

        for (int i = num_amount - start_place + 1; i < get_length; i++)
        {
            num_and_status[start_place + i - num_amount - 1][0] = current_num_status[i][0];
            num_and_status[start_place + i - num_amount - 1][1] = current_num_status[i][1];
        }
    }
}


// Draw a 5 num selector to control num_status.
// num_status is 0 or 1.
// num_amount > 5
void ControlNumStatus(int num_amount, int num_and_status[][2])
{
    unsigned int key;
    int **current_num_status;
    int start_place = 1;


    do 
    {
        // get currnet num status
        current_num_status = GetCurrnetNumStatus(start_place, 5, num_amount, num_and_status);

        key = KEY_CHAR_0; //reset key
        
        while (key != KEY_CTRL_F6 && key != KEY_CTRL_EXE)
        {
            DrawNumButton(current_num_status);

            GetKey(&key); // get the current key

            switch (key)
            {
            case KEY_CTRL_F1: current_num_status[0][1] = !current_num_status[0][1]; break;

            case KEY_CTRL_F2: current_num_status[1][1] = !current_num_status[1][1]; break;

            case KEY_CTRL_F3: current_num_status[2][1] = !current_num_status[2][1]; break;

            case KEY_CTRL_F4: current_num_status[3][1] = !current_num_status[3][1]; break;

            case KEY_CTRL_F5: current_num_status[4][1] = !current_num_status[4][1];
            }
        }

        // put currnet num status
        PutCurrnetNumStatus(current_num_status, start_place, 5, num_amount, num_and_status);

        // move start_place
        if (start_place < num_amount)
            start_place++;
        else start_place = 1;
    }
    while (key != KEY_CTRL_EXE);
    
    free(current_num_status);
}




#ifdef __cplusplus
}
#endif