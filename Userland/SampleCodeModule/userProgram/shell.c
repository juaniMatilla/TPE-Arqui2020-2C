#include "shell.h"

extern void invalid_opcode();

void info();
void printMem(int c);
int execute(char *command);
int fromChess = 0;

int StartShell(int chessFlag){
  fromChess = chessFlag;
  consoleSize(1016, 0, 760, 0);
  clearDisplay(0);

  print("Modulos:\n");
  info();
  print("¿Que modulo desea correr?\n");
  char command[50];
  int i;
  char buff;
  while(1){ 
    i=0;
    print("$ ");
    while(buff != '\n'){
         if(getchar(&buff) == 1){
            if(buff == '\b'){
              putchar(buff);
              if(i>0)
                i--;
            }else{
              putchar(buff);
              command[i++] = buff;  
            }
          }
    }
    command[i] = 0;
    buff = 0;
    if(execute(command))
      return 0;
  }
    
}

void info(){
    print(" inforeg: Muestra el valor de los registros\n");
    print(" date: Muestra el la hora y fecha actual\n");
    print(" chess: Abre un juego de ajedrez\n");
    print(" excpetions0: excepción de divivion por cero \n");
    print(" excpetions1: excepción de código de operación inválido \n");
    print(" printMem (puntero): Dado un puntero imprime el valor de los 32 bytes siguientes\n");
    print(" help: Muestra los comandos disponibles\n");
    if(fromChess){
      print("resume: vuelve a el juego guardado\n");
    }

}

//void printMem(int c){
//    uint64_t buffer[32];
//    getFromAdress(buffer[0], 32, c);
//    for (int i = 0; i < 32; i++){
//      char aux[2];
//      hexToStr(buffer[0], aux[0]);
//      putStirng(aux[0]);
//    }    
//}

int execute(char *command){
  if(strcmp(command,"help") == 0){
    info();
  }else if(strcmp(command,"exception0") == 0){
    consoleSize(1016, 0, 768, 0);
    clearDisplay(0);
    divByZero();
  }else if(strcmp(command,"exception6") == 0){
     consoleSize(1016, 0, 768, 0);
     clearDisplay(0);
     invalid_opcode();
  }else if(strcmp(command,"inforeg") == 0){
    print("inforeg:\n");
    getRegistersValues();
    print("\n");
  }else if(strcmp(command,"date") == 0){
     print("date : ");
     char buff[17];
     StringDataTime(buff[0]);
     putStirng(buff[0]);
    }else if(strcmp(command,"printMen") == 0){
    print("ingrese la direcion:\n");
    char address[20] = {0};
    char buff;
    int i = 0;
    while(buff != '\n'){
         if(getchar(&buff) == 1){
            if(buff == '\b'){
              putchar(buff);
              if(i>0)
                i--;
            }else{
              putchar(buff);
              address[i++] = buff;  
            }
          }
    }
    getFromAddress(address);
    
  }else if(strcmp(command,"resume") == 0){
    if(fromChess == 1)
      return 1;
    else
      print("No hay juego guardado\n");   
  }else if(strcmp(command,"chess") == 0){
    clearDisplay(0);
    playchess();
    clearDisplay(0);
    consoleSize(1024, 0, 768, 0);
    print("Modulos:\n");
    info();
    print("¿Que modulo desea correr?\n");
  }else {
    print("Comando inexistente\n");
  }
  return 0;
}

void divByZero(){
  int num = 10/0;
}

