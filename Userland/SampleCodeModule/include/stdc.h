#ifndef STDC_H
#define STDC_H

#include <stdint.h>
#include <stdarg.h> //permite arumentos variables
#include <stdAsm.h>

//manejo de consola:
void consoleSize(int maxX, int minX, int maxY, int minY);
void clearDisplay(unsigned int backgroundColor);
void print(const char *format, ...);
void putStirng(char *String); //imprime un string
void putchar(char c); //imprime un caeacter
void putInt(int num);

//manejo del display
void Matrix16x16(int x, int y, unsigned char* matriz, int fontSize, int fontColor, int backgroundColor);

//manejo del teclado
void getchar(char c);
unsigned int scan(char * buffer, unsigned int len);

#endif