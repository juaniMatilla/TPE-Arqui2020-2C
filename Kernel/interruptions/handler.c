#include <handler.h>

void testerTick(){
    ncNewline();
    ncPrint("hola");
    return;
}

void testerkeyboard(){
    char aux = _readKey();
    ncPrintChar(aux);
    return;
}

void redPrint(const char* buff){
    textPrint(buff, 15, 0);
    return;
}

void print(const char* buff){
    textPrint(buff, 4, 0);
    return;
}


