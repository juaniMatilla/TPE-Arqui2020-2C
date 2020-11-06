#ifndef STDASM_H
#define STDASM_H

#include <stdint.h>

void SystemCall00(const char *format); //imprime un String

void SystemCall01(char c); //imprime un caracter

void SystemCall02(int maxX, int minX, int maxY, int minY);  //setConsoleSize

void SystemCall03(int x, int y, unsigned char* matriz, int fontSize, int fontColor, int backgroundColor);  //drawFont16x16

void SystemCall04(unsigned int backgroundColor); //clearDisplay

void SystemCall05(char *buffer,int dim); //devulve una tecla

void SystemCall06(int * target); //devulve una tecla

//unsigned int SystemCall08(char *buffer,int dim); //devulve una tecla

#endif 