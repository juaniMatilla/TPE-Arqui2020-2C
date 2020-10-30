#include "text_driver.h"

char* screen_start = (char*) 0xb8000;
/*
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    Pink = 13,
    Yellow = 14,
    White = 15,
*/

void textPrint(char* mensaje, int color, int background){
    int colorCode = (background <<4 | color);
    while( *mensaje != '\0' ){
        *screen_start = *mensaje ;
        screen_start[1]  = colorCode;
        screen_start +=2;
        mensaje++;
    }
}
