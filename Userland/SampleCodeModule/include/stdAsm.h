#ifndef STDASM_H
#define STDASM_H

#include <stdint.h>

void SystemCall00(const char *format); //imprime un String
void SystemCall01(char c); //imprime un caracter
void SystemCall02(char *Matrix);
char* SystemCall03(void);


#endif 