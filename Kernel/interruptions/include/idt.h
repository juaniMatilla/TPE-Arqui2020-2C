#ifndef LIB_IDT_H
#define LIB_IDT_H

#include <stdint.h>
#include <defs.h>
#include <lib.h>
#include <stdarg.h> //permite arumentos variables

#include <video_driver.h>
#include <keyboard_driver.h>
#include <timerRTC.h>
#include <memory_driver.h>

/* Descriptor de interrupcion */
typedef struct {
  uint16_t offset_l;
  uint16_t selector;
  uint8_t cero;
  uint8_t access;
  uint16_t offset_m;
  uint32_t offset_h;
  uint32_t other_cero;
} DESCR_INT;

void load_idt();
void irqDispatcher(uint64_t irq);
void exDispatcher(uint64_t num, uint64_t *RIP, uint64_t *RSP);
void int80Handler(uint64_t num, uint64_t *RIP);
uint64_t* int81Handler(uint64_t *RIP, uint64_t *RSP);

#endif