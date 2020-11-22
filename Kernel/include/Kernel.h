#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>

#include <text_driver.h>
#include <timerRTC.h>
#include "video_driver.h"
#include "idt.h"
#include <lib.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;


extern uint64_t * _b_rip;
extern uint64_t * _b_rsp;


#endif