#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>
#include <lib.h>
#include <memory_driver.h>

//scancodes de teclas especiales
#define CONTROL_PRESSED 29
#define CONTROL_RELEASED 157
#define LEFT_SHIFT_PRESSED 42
#define LEFT_SHIFT_RELEASED 170
#define RIGHT_SHIFT_PRESSED 54
#define RIGHT_SHIFT_RELEASED 182
#define BLOQMAYUS 58
#define F1 59

#define INPUT_BUFFER 255 //Cant max de caracteres en buffer de input

void readStandardInput(char * buffer,int dim);
void keyboard_handler(uint64_t *TOP);
void KBsize(int * target); //dim buffer teclado
#endif