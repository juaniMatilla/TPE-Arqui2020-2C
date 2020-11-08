#include <stdint.h>
#include <lib.h>
#include <keyboard_driver.h>

//scancodes de teclas especiales
#define CONTROL_PRESSED 29
#define CONTROL_RELEASED 157
#define LEFT_SHIFT_PRESSED 42
#define LEFT_SHIFT_RELEASED 170
#define RIGHT_SHIFT_PRESSED 54
#define RIGHT_SHIFT_RELEASED 182
#define BLOQMAYUS 58

#define INPUT_BUFFER 255 //Cant max de caracteres en buffer de input

static char keyboardBuffer[INPUT_BUFFER];
static unsigned int bufferSize = 0;
static unsigned int bufferIndex = 0;
static unsigned int olderLetter = 0;

//estado de teclas especiales
static int pressingShift =0;
static int bloqMayus = 0; //boolean
static int pressingCtrl =0;


static char asccode[58][2] ={
    { 0, 0 }, { 0, 0 }, { '1','!' }, { '2','@' },
    { '3','#' }, { '4','$' }, { '5','%' }, { '6','^' },
    { '7','&' }, { '8','*' }, { '9','(' }, { '0',')' },
    { '-','_' }, { '=','+' }, {'\b','\b'}, {'\t','\t'},
    { 'q','Q' }, { 'w','W' }, { 'e','E' }, { 'r','R' },
    { 't','T' }, { 'y','Y' }, { 'u','U' }, { 'i','I' },
    { 'o','O' }, { 'p','P' }, { '[','{' }, { ']','}' },
    {'\n','\n'}, {   0,0   }, { 'a','A' }, { 's','S' },
    { 'd','D' }, { 'f','F' }, { 'g','G' }, { 'h','H' },
    { 'j','J' }, { 'k','K' }, { 'l','L' }, { ';',':' },
    {'\'','\"'}, { '`','~' }, {   0,0   }, { '\\','|'},
    { 'z','Z' }, { 'x','X' }, { 'c','C' }, { 'v','V' },
    { 'b','B' }, { 'n','N' }, { 'm','M' }, { ',','<' },
    { '.','>' }, { '/','?' }, {   0,0   }, {   0,0   },
    {   0,0   }, { ' ',' ' }
};

void readStandardInput(char * buffer,int dim) {
  olderLetter = bufferIndex - bufferSize;
  if(olderLetter < 0){
    olderLetter = INPUT_BUFFER + olderLetter;
  }
  for (int i = 0; i < dim; i++){
    buffer[i] = keyboardBuffer[(olderLetter++)%INPUT_BUFFER];
    bufferSize--;
  }
  
}

void keyboard_handler(){
    int code = getKeyScanCode();
    if(code==CONTROL_PRESSED)
      pressingCtrl=1;
    else if(code == CONTROL_RELEASED)
      pressingCtrl=0;
    else if(code == LEFT_SHIFT_PRESSED || code == RIGHT_SHIFT_PRESSED)
      pressingShift=1;
    else if (code== LEFT_SHIFT_RELEASED || code == RIGHT_SHIFT_RELEASED)
      pressingShift=0;
    else if(code==BLOQMAYUS)
      bloqMayus = !bloqMayus;
    else if (code < 58) { //Si es una tecla presionada
    int auxMayus = (bloqMayus | pressingShift);
    keyboardBuffer[(bufferIndex++)%INPUT_BUFFER] = asccode[code][auxMayus];
    bufferSize++;
  }
}
void KBsize(int * target) {
  *target = bufferSize;
}
  
