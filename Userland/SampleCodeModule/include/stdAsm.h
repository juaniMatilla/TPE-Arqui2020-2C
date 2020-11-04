#ifndef STDASM_H
#define STDASM_H

#include <stdint.h>

void SystemCall00(const char *format); //imprime un String

void SystemCall01(char c); //imprime un caracter

void SystemCall02(int x, int y, unsigned char* matriz, int fontSize, int fontColor, int backgroundColor);

char* SystemCall03(void); //devulve una tecla


#endif 