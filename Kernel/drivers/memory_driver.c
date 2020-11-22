#include <memory_driver.h>

#define REGISTERS_SIZE 19
static uint64_t registers[REGISTERS_SIZE];

//leer memoria
//void getFromAdress(uint64_t *buffer, uint64_t address){
//    *buffer =  getMemoryValue(address);
//}

void getFromAdress(uint64_t address, uint64_t * target, uint8_t totalBytes) {
    uint64_t * pos = (uint64_t *) address;
    *target = getMemoryValue(pos);
  
}

//manejo de registros
uint64_t* saveRegisters(uint64_t *TOP){

    for (int i = 0; i < REGISTERS_SIZE; i++){
        registers[i] = TOP[i];
    }
    return registers;
}

uint64_t* getRegisters(){
    return registers;
}

void printRegister(uint64_t* aux){
    char* RegistersName[] = {"R15","R14","R13","R12","R11","R10","R9","R8",
    "RSI","RDI","RBP","RDX","RCX","RBX","RAX","RIP", "CS", "FLAGS","RSP"};
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

//funciones auxiliares
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