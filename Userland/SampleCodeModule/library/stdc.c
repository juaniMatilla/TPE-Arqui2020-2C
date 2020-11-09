#include <stdc.h>
//general
//pasa un int de dos digitos a un char en buff
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

void intToStr(int num, char *buff){
    if (num == 0){
        buff[0] = '0';
        buff[1] = '\0';
        return;
    }
    int j= 0;
    int i = 0;
    while (num != 0){
        buff[i++] = num % 10 + '0';
        num = num / 10;
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

void numTwoDigitsToStr(int num, char* buff){
    for (int i = 1; i >= 0; i--){
        int aux = num%10;
        buff[i] = (aux) +'0';
        num = num/10;
    }
    return;   
}

unsigned int strlen(char * str){
    int i=0;
    while (str[i]!=0){
        i++;
    }
    return i;
}

void strUnion(char* buff, char* str, int desde, int dim){
    for (int i = 0; i < dim; i++){
        buff[i+desde] = str[i];
    }
    return;
}

int strcmp(char *str1,char *str2){
    for(int i=0;str1[i]&&str2[i];i++){
        if(str1[i] != str2[i]){
            return 1;
        }
    }
    return 0;
}

//manejo del teclado////////////////////////////////////////////////////////
int getchar(char* c){
   int aux = 0;
   SystemCall06(&aux);
   if(aux){
       SystemCall05(c,1);
       if(c == '\b'){
           SystemCall07();
       }
       return 1;
   }
    return 0;
}

int scan(char * buffer, int len){
    if(len < 1){
        return 0;
    }
    if(len == 1){
        buffer[len-1] = '\n';
        return 1;
    }
    int aux = 0;
    SystemCall06(&aux);
    if(aux == len){
        SystemCall05(buffer, len -2);
        buffer[len-1] = '\n';
        return 1;
    }
    return 0;
}
//hora y fecha////////////////////////////////////////////////////////////////////
int getSeconds() {
	int result = 0;
    SystemCall08(0,&result);
    return result;
}

int getMinutes() {
	int result = 0;
    SystemCall08(1,&result);
    return result;
}
int strcmp(char *str1,char *str2){
    for(int i=0;str1[i]&&str2[i];i++){
        if(str1[i] != str2[i]){
            return 1;
        }
    }
    return 0;
}


int getHours() {
	int result = 0;
    SystemCall08(2,&result);
    return result-3;
}

int getDay() {
	int result = 0;
    SystemCall08(3,&result);
    return result;
}

int getMonth() {
	int result = 0;
    SystemCall08(4,&result);
    return result;
}

int getYear() {
	int result = 0;
    SystemCall08(5,&result);
    return result;
}

//pasar un buffer de dim 17
void StringDataTime(char* buffer) {
	int seconds = getSeconds();
	int minutes = getMinutes();
	int hours = getHours();
	int day = getDay();
	int month = getMonth();
	int year = getYear();
	char aux[2];
	
    numTwoDigitsToStr(day, aux);
    strUnion(buffer, aux, 0, 2);

	buffer[2] = '/';

	numTwoDigitsToStr(month, aux);
	strUnion(buffer, aux, 3, 2);

	buffer[5] = '/';

	numTwoDigitsToStr(year, aux);
	strUnion(buffer, aux, 6, 2);

	buffer[8] = ' ';

	numTwoDigitsToStr(hours, aux);
	strUnion(buffer, aux, 9, 2);

	buffer[11] = ':';

	numTwoDigitsToStr(minutes, aux);
	strUnion(buffer, aux, 12, 2);

	buffer[14] = ':';

	numTwoDigitsToStr(seconds, aux);
	strUnion(buffer, aux, 15, 2);

    buffer[17] = '\n';  
}
//registros y memoria /////////////////////////////////////////////
void getRegistersValues(){
    char* RegistersName[] = {"R15","R14","R13","R12","R11","R10","R9","R8",
    "RSI","RDI","RBP","RDX","RCX","RBX","RAX","RIP"};
    uint64_t* Registers = SystemCall09();
    
    putStirng("registros: \n");
    for (int i = 0; i < 16; i++){
        print("%s = %x,  ",RegistersName[i] , Registers[i]);    
    }
}

void getFromAdress(uint8_t* buffer, int cantBytes, uint64_t address){
    uint64_t* aux = (uint64_t*) address;
    for (int i = 0; i < cantBytes; i++){
        SystemCall10(buffer[i], aux[i]);
    }
}

//manejo de consola///////////////////////////////////////////////////////////////////
void consoleSize(int maxX, int minX, int maxY, int minY){
    SystemCall02(maxX, minX, maxY, minY);
}

void clearDisplay(unsigned int backgroundColor){
    SystemCall04(backgroundColor);
}

void print(const char *format, ...){
    va_list ap;
    va_start(ap, format);
    uint8_t *ptr;

    for (ptr = format; *ptr != '\0'; ptr++){
        if (*ptr == '%'){
            ptr++;
            switch (*ptr){
                case 's':
                    putStirng(va_arg(ap, char*));
                break;
                case 'd':
                    putInt(va_arg(ap, int));
                break;
                case 'x':
                    putHex(va_arg(ap, int));
                break;
                case '%':
                    putchar('%');
                break;
            }
        }else{
            putchar(*ptr);
        }
    }
    va_end(ap);
}

void Matrix16x16(int x, int y, unsigned char* matriz, int fontSize, int fontColor, int backgroundColor){
    SystemCall03(x, y, matriz, fontSize, fontColor, backgroundColor);
    return;
}

void putStirng(char *String){
    SystemCall00(String);
    return;
}

void putInt(int num){
    char buff[20] = {'0'};
    intToStr(num, buff);
    putStirng(buff);
    return;
}

void putHex(int num){
    char buff[20] = {'0'};
    hexToStr(num, buff);
    putStirng(buff);
    return;
}

void putchar(char c){
    SystemCall01(c);
}
