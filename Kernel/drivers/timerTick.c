#include  <timerTick.h>

static int counter = 0;
static int flag = 0;
static uint64_t ticks = 0;

void delay(int cantTimerTick){  //se le pasa la cantidad de ciclos de 50ms
    counter = 0;
    flag = 1;
    while(counter <= cantTimerTick){
        _hlt();
    }
    flag = 0;
}

void timerTickConuter(){
    if(flag == 1){
        counter++;
    }
    ticks++;
}

uint64_t getTicks(){
    return ticks;
}