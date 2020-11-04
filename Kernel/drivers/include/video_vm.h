#ifndef VIDEO_VM_H
#define VIDEO_VM_H

#include <stdint.h>
#include "font.h"

//funciones manejo de pantalla
void init_VM_Driver();

void scrollUp(int cant, unsigned int backgroundColor);
void clearDisplay(unsigned int backgroundColor);
void drawPixel(unsigned int x, unsigned int y, int color);
void drawRectangle(unsigned int x, unsigned int y, int b, int h, int color);
void drawSquare(unsigned int x, unsigned int y, int l, int color);
int drawChar(int x, int y, char character, int fontSize, int fontColor, int backgroundColor);
void drawFont16x16(int x, int y, unsigned char* matriz, int fontSize, int fontColor, int backgroundColor);

void setConsoleSize(int maxX, int minX, int maxY, int minY);
void writeConsole(const char* String);
void writeCharConsole(char character);
void newLineConsole();
void scrollUpConsole();

#endif

//color 0 -> negro, 16777215 -> blanco