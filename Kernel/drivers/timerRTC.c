#include "timerRTC.h"

//private function:
void strUnion(char* buff, char* str, int desde, int dim);
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

void getDataTime(int mode, int* result){
	switch(mode) {
    case 0: 
		*result = getSeconds();
    	break;
    case 1: 
		*result = getMinutes();
    	break;
    case 2: 
		*result = getHours();
    	break;
    case 3: 
		*result = getDay();
    	break;
    case 4: 
		*result = getMonth();
    	break;
    case 5: 
		*result = getYear();
    	break;
  }
}
/*
//cambiar que reciba un buff, que no use una variable local
void StringDataTime(char *buffer) {
	int seconds = getSeconds();
	int minutes = getMinutes();
	int hours = getHours()-3;

	int day = getDay();
	int month = getMonth();
	int year = getYear();
    
	char aux[2];
	
    intToStr(day, aux);
    strUnion(buffer, aux, 0, 2);

	buffer[2] = '/';

	intToStr(month, aux);
	strUnion(buffer, aux, 3, 2);

	buffer[5] = '/';

	intToStr(year, aux);
	strUnion(buffer, aux, 6, 2);

	buffer[8] = ' ';

	intToStr(hours, aux);
	strUnion(buffer, aux, 9, 2);

	buffer[11] = ':';

	intToStr(minutes, aux);
	strUnion(buffer, aux, 12, 2);

	buffer[14] = ':';

	intToStr(seconds, aux);
	strUnion(buffer, aux, 15, 2);

    buffer[17] = '\n';

}

//copia todo el vector str en buff desde la posicion 'desde' inclusive  
//dim: dimencion de str
void strUnion(char* buff, char* str, int desde, int dim){
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
*/