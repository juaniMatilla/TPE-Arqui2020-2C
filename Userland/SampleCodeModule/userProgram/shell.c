#include "shell.h"
void info();
void printMem(char* c);
void execute(char *command);
int strcmp(char *str1,char *str2);

void StartShell(){
    print(" Modulos:\n");
    info();
    char c = 0;
    print("\n ¿Que modulo desea correr? $ ");
    char command[99];
    int i = 0;
    while ( (c = getchar()  ) != -1){
        putchar(c);
        command[i++] = c;
        if(c == '\n'){
            execute(command);
            print("\n ¿Que modulo desea correr? $ ");
        }
    }
    
}

void info(){
    print(" inforeg: Muestra el valor de los registros\n");
    print(" date: Muestra el la hora y fecha actual\n");
    print(" chess: Abre un juego de ajedrez\n");
    print(" excpetions: Permite ver mediante operaciones matematicas que las excepciones funcionan correctamente\n");
    print(" printMem (puntero): Dado un puntero imprime el valor de los 32 bytes siguientes\n");
}


void printMem(char* c){
    for(int i = 0;i < 4;i++){
        //printF("%h\n",c++);
    }
}

void date(){
    //print(getDate());
}

void inforeg(){
    //int *registers = getRegisters();
}

void execute(char *command){
  if(strcmp(command,"help") == 0){
    //help();
  }else if(strcmp(command,"exceptions") == 0){
    //exceptions();
  }else if(strcmp(command,"inforeg") == 0){
    //inforeg();
  }else if(strcmp(command,"date") == 0){
    //date();
  }else if(strcmp(command,"chess") == 0){
    //chess();
  }else{
    char *str = "printMem ";
    int i;
    for(i = 0;str[i];i++){
        if(command[i] != str[i]){
            return;
        }
    }
    //printMem(strToInt(command[i]));
  }
}

int strcmp(char *str1,char *str2){
    for(int i=0;str1[i]&&str2[i];i++){
        if(str1[i] == str2[i]){
            return 0;
        }
    }
    return 1;
}





