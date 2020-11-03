#ifndef LIB_IDT_H
#define LIB_IDT_H

#include <stdint.h>
#include <defs.h>
#include <lib.h>
#include <stdarg.h> //permite arumentos variables

#include <video_vm.h>
#include <keyboard_driver.h>
#include <timerRTC.h>


void load_idt();
void irqDispatcher(uint64_t irq);
void exDispatcher(uint64_t ex);
void int80Handler(uint64_t num, uint64_t *RIP);

#endif