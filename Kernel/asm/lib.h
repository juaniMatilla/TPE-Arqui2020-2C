#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);
int getTimeInfo(int num);

void _sti();
void _cli();
void _picMasterMask(uint8_t mask);
void _picSlaveMask(uint8_t mask);
uint8_t getKeyScanCode();
uint64_t getMemoryValue(uint64_t address);

void _ex00Handler(); //DivByZero
void _ex01Handler(); // 

void _irq00Handler(); //timer tick
void _irq01Handler(); //keyboard
void _irq08Handler(); //RTC

//las interupciones de software
void _irq80Handler(); 
void _irq81Handler();

#endif