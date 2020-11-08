#include <memory_driver.h>

#define REGISTERS_SIZE 16
static uint64_t registers[REGISTERS_SIZE];


void getFromAdress(uint8_t *buffer, uint64_t address){
    *buffer =  getMemoryValue(address);
}

uint64_t* saveRegisters(uint64_t *RSP, uint64_t *RIP){

    for (int i = 0; i < REGISTERS_SIZE-1; i++){
        registers[i] = RSP[i];
    }
    registers[REGISTERS_SIZE-1] = RIP[0];
    return registers[0];
}

void printRegister(uint64_t* aux){
    char* RegistersName[] = {"R15","R14","R13","R12","R11","R10","R9","R8",
    "RSI","RDI","RBP","RDX","RCX","RBX","RAX","RIP"};
    writeConsole("Registers: \n");
    for (int i = 0; i < REGISTERS_SIZE; i++){
        writeConsole(RegistersName[i]);
        writeConsole(":  ");
        char aux[10];
        hexToStr(registers[i], aux[0]);
        writeConsole(aux[0]);
         writeConsole("\n");
    }
}


void hexToStr(int num, char *buff){
    if (num == 0){
        buff[0] = '0';
        buff[1] = '\0';
        return;
    }
    int j= 0;
    int i = 0;
    while (num != 0){
        int aux = num % 16;
        if(aux <10){
            buff[i++] = aux + '0';
        }else{
            buff[i++] = aux-10 + 'a';
        }    
        num = num / 16;
    }
    buff[i] = '\0';
    i--;
    char aux;
    while(j<i){
        aux = buff[i];
        buff[i] = buff[j];
        buff[j]=aux;
        j++;
        i--;
    }
    return;
}