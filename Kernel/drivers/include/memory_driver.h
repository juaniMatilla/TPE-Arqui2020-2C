#ifndef MEMORY_DRIVER_H
#define MEMORY_DRIVER_H

#include <stdint.h>
#include <lib.h>




void getFromAdress(uint64_t address, uint64_t * target, uint8_t totalBytes);

void printRegister(uint64_t* aux);  //imprime los regitros
uint64_t* getRegisters();
uint64_t* saveRegisters(uint64_t *TOP);


#endif