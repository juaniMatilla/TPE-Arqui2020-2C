#include "timerRTC.h"

//private function:
void concaChar(char* buff, char* str, int desde, int dim);
void intToStr(int num, char* buff);
 
int getSeconds() {
  return getTimeInfo(0);
}

int getMinutes() {
  return getTimeInfo(2);
}

int getHours() {
  return getTimeInfo(4);
}

int getDay() {
  return getTimeInfo(7);
}

int getMonth() {
  return getTimeInfo(8);
}

int getYear() {
  return getTimeInfo(9);
}

//cambiar que reciba un buff, que no use una variable local
char* getDataTime() {
	int seconds = getSeconds();
	int minutes = getMinutes();
	int hours = getHours()-3;

	int day = getDay();
	int month = getMonth();
	int year = getYear();
    
    char result[20] ;
	char aux[2];
	
    intToStr(day, aux);
    concaChar(result, aux, 0, 2);

	result[2] = '/';

	intToStr(month, aux);
	concaChar(result, aux, 3, 2);

	result[5] = '/';

	intToStr(year, aux);
	concaChar(result, aux, 6, 2);

	result[8] = ' ';

	intToStr(hours, aux);
	concaChar(result, aux, 9, 2);

	result[11] = ':';

	intToStr(minutes, aux);
	concaChar(result, aux, 12, 2);

	result[14] = ':';

	intToStr(seconds, aux);
	concaChar(result, aux, 15, 2);

    result[17] = '\n';

	return result;
}

//copia todo el vector str en buff desde la posicion 'desde' inclusive  
//dim: dimencion de str
void concaChar(char* buff, char* str, int desde, int dim){
    for (int i = 0; i < dim; i++){
        buff[i+desde] = str[i];
    }
    return;
}

//pasa un int de dos digitos a un char en buff
void intToStr(int num, char* buff){
    for (int i = 1; i >= 0; i--){
        int aux = num%10;
        buff[i] = (aux) +'0';
        num = num/10;
    }
    return;   
}
