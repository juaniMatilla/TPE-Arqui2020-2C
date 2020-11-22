#ifndef TIMER_TICK_H
#define TIMER_TICK_H

#include <stdint.h>
#include <lib.h>
#include <video_driver.h>  //despues sacra es para el test

void delay(int cantTimerTick);
void timerTickConuter();
uint64_t getTicks();

#endif