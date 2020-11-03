#include <stdc.h>

void getchar()
{
}
void scanf()
{
}

//general
//pasa un int de dos digitos a un char en buff
void intToStr(int num, char *buff){
    int aux = num;

    if (num == 0){
        buff[0] = '0';
        buff[1] = '\0';
        return;
    }

    int i = 0;
    while (num != 0){
        buff[i++] = num % 10 + '0';
        num = num / 10;
    }

    if (aux < 0){
        buff[i++] = '-';
    }

    buff[i] = '\0';

    for (int t = 0; t < i / 2; t++){
        buff[t] ^= buff[i - t - 1];
        buff[i - t - 1] ^= buff[t];
        buff[t] ^= buff[i - t - 1];
    }
    return;
}

//imprimir en pantalla
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