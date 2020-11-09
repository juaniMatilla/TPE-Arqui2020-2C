#include "shell.h"
void info();
void printMem(char* c);
void execute(char *command);
int strcmp(char *str1,char *str2);
int strToInt(char a[]);
void StartShell(){
  //playchess();
  consoleSize(1016, 0, 768, 0);
  clearDisplay(0);
  print("Modulos:\n");
  info();
  print("¿Que modulo desea correr?\n");
  char *command;
  int i;
  char buff;
  while(1){ 
    i=0;
    print("$ ");
    while(buff != '\n'){
        if(getchar(&buff) == 1){
            putchar(buff);
            command[i++] = buff;
        }
    }
    command[i] = 0;
    buff = 0;
    execute(command);
  }
    
}

void info(){
    print(" inforeg: Muestra el valor de los registros\n");
    print(" date: Muestra el la hora y fecha actual\n");
    print(" chess: Abre un juego de ajedrez\n");
    print(" excpetions: Permite ver mediante operaciones matematicas que las excepciones funcionan correctamente\n");
    print(" printMem (puntero): Dado un puntero imprime el valor de los 32 bytes siguientes\n");
    print(" help: Muestra los comandos disponibles\n");

}


void printMem(char* c){
    for(int i = 0;i < 4;i++){
      print("%d\n",c++);
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
    info();
  }else if(strcmp(command,"exceptions") == 0){
     print("excep\n");
    //exceptions();
  }else if(strcmp(command,"inforeg") == 0){
     print("inforeg\n");
    //inforeg();
  }else if(strcmp(command,"date") == 0){
     print("date\n");
    //date();
  }else if(strcmp(command,"chess") == 0){
    clearDisplay(0);
    playchess();
    clearDisplay(0);
    consoleSize(1024, 0, 768, 0);
  }else{
    char *str = "printMem ";
    int i;
    for(i = 0;str[i];i++){
        if(command[i] != str[i]){
            print("Comando no existente\n");
            return;
        }
    }
    printMem(strToInt(command[i]));
  }
}

int strcmp(char *str1,char *str2){
    for(int i=0;str1[i]&&str2[i];i++){
        if(str1[i] != str2[i]){
            return 1;
        }
    }
    return 0;
}


  
int strToInt(char a[]) {
  int c, sign, offset, n;

  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }

  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }

  n = 0;

  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }

  if (sign == -1) {
    n = -n;
  }

  return n;
}