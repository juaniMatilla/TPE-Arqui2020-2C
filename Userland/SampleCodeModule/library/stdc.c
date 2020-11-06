#include <stdc.h>

void getchar(char c){
    SystemCall05(&c,1);
    return;
}

unsigned int scan(char * buffer, unsigned int len) {
    return SystemCall05(buffer, len);
}

/*unsigned int strlen(char * str){
    int i=0;
    while (str[i]!=0){
        i++;
    }
    return i;
}*/
//general
//pasa un int de dos digitos a un char en buff
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

//manejo de consola
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

void putchar(char c){
    SystemCall01(c);
}
