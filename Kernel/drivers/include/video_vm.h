#ifndef VIDEO_VM_H
#define VIDEO_VM_H

#include <stdint.h>
#include "font.h"

void init_VM_Driver();
void drawPixel(unsigned int x, unsigned int y, int color);
void drawRectangle(unsigned int x, unsigned int y, int b, int h, int color);
void drawSquare(unsigned int x, unsigned int y, int l, int color);
void scrollUp(int cant, unsigned int backgroundColor);

int drawChar(int x, int y, char character, int fontSize, int fontColor, int backgroundColor);

void drawString(int x, int y, const char* String, int fontSize, int fontColor, int backgroundColor);

#endif

//color 0 -> negro, 16777215 -> blanco