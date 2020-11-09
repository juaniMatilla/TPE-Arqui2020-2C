#ifndef STDASM_H
#define STDASM_H

#include <stdint.h>

void SystemCall00(const char *format); //imprime un String

void SystemCall01(char c); //imprime un caracter

void SystemCall02(int maxX, int minX, int maxY, int minY);  //setConsoleSize

void SystemCall03(int x, int y, unsigned char* matriz, int fontSize, int fontColor, int backgroundColor);  //drawFont16x16

void SystemCall04(unsigned int backgroundColor); //clearDisplay

void SystemCall05(char *buffer,int dim); //devulve una tecla

void SystemCall06(int * target); //deculve el tamaño del buffer del teclado
 
void SystemCall07();  //hace un backspace

void SystemCall08(char mode,int* dim); //devulve los datos de la feha o hora selecionados

uint64_t* SystemCall09(); //devulve una estructura con los registros

void SystemCall10(uint8_t *buffer, uint64_t address); //devuelve 1byte de la dirrecion de memoria

#endif 