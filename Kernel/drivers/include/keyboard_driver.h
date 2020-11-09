#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>
#include <lib.h>

void readStandardInput(char * buffer,int dim);
void keyboard_handler();
void KBsize(int * target); //dim buffer teclado
#endif