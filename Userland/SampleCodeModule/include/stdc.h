#ifndef STDC_H
#define STDC_H

#include <stdint.h>
#include <stdarg.h> //permite arumentos variables
#include <stdAsm.h>

//manejo de consola:
void String(int x, int y, char *String);
void consoleSize(int maxX, int minX, int maxY, int minY);
void clearDisplay(unsigned int backgroundColor);
void print(const char *format, ...);
void putStirng(char *String); //imprime un string
void putchar(char c); //imprime un caeacter
void putHex(int num);
void putInt(int num);
void putHex(int num);

//manejo del display
void Matrix16x16(int x, int y, unsigned char* matriz, int fontSize, int fontColor, int backgroundColor);

//manejo del teclado
int getchar(char* c);
int scan(char * buffer, int len);

//fecha y hora
uint64_t getMillis();
int getSeconds();
int getMinutes();
int getHours();
int getDay();
int getMonth();
int getYear();
void StringDataTime(char* buffer);//pasar un buffer de dim 17

//registros
void getRegistersValues();
void getFromAddress(char* address);

//otros
int strToInt(char a[]);
void intToStr(int num, char *buff);
void hexToStr(int num, char *buff);
unsigned int strlen(char * str);
void numTwoDigitsToStr(int num, char* buff);
void strUnion(char* buff, char* str, int desde, int dim);
int strcmp(char *str1,char *str2);

#endif