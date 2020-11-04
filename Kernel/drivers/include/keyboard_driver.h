#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>
#include <lib.h>

//void getKeyPressed(char* c);
unsigned int readStandardInput(char * buffer,int dim);
void keyboard_handler();
#endif