#ifndef MEMORY_DRIVER_H
#define MEMORY_DRIVER_H

#include <stdint.h>
#include <lib.h>




void getFromAdress(uint8_t *buffer, uint64_t address);
void printRegister(uint64_t* aux);


#endif