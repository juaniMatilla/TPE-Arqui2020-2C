#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>
#include <lib.h>

int getScanCode();
int isLetter(char c);
void onKeyPressed(char chr);

char getKey();





#endif