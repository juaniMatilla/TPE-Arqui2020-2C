#include <stdint.h>

main();

void printMem(char* c){
    for(int i = 0;i < 4;i++){
        printF("%h\n",c++);
    }
}