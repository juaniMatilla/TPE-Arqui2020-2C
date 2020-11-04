#ifndef STDC_H
#define STDC_H

#include <stdint.h>
#include <stdarg.h> //permite arumentos variables
#include <stdAsm.h>

void print(const char *format, ...);
void putStirng(char *String); //imprime un string
void putchar(char c); //imprime un caeacter
void putInt(int num);

void putMatrix(int x, int y, unsigned char* matriz, int fontSize, int fontColor, int backgroundColor);

char getchar();

#endif