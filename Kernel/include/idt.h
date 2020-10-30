#ifndef LIB_IDT_H
#define LIB_IDT_H

#include <stdint.h>
#include <stdarg.h> //permite arumentos variables
#include <defs.h>
#include <lib.h>
#include <handler.h>

void load_idt();
void writeIDT();
void irqDispatcher(uint64_t irq);
void exDispatcher(uint64_t ex);
void int80Handler(uint64_t num, ...);

#endif