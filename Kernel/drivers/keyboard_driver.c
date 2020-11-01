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
#define ENTER 28
#define ESC_SCANCODE 0x81
#define ESC_ASCII 27
#define CAPTURE_FLAGS 2
#define ALT_SCAN_CODE 0xb8
//estado de teclas especiales
static int pressingShift =0;
static int bloqMayus = 0;
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


int codeMatchesAscii(int scancode){
  return scancode>=0 && scancode<58 && asccode[scancode][1] !=0;
}

int getScanCode(){
  int code = kbFlag();// funcion asembler 
  if(code == CONTROL_PRESSED)
    pressingCtrl = 1;
  else if(code == CONTROL_RELEASED)
    pressingCtrl = 0;
  else if(code == LEFT_SHIFT_PRESSED || code == RIGHT_SHIFT_PRESSED)
    pressingShift = 1;
  else if (code== LEFT_SHIFT_RELEASED || code == RIGHT_SHIFT_RELEASED)
    pressingShift=0;
  else if(code == BLOQMAYUS)
    bloqMayus = !bloqMayus;
  return code;
}

int isLetter(char c){
  return (c>='a' && c<='z') || (c>='A' && c<='Z');
}

char getMatchingAscii(int scancode){
  if(codeMatchesAscii(scancode)){
    if( bloqMayus && isLetter( asccode[scancode][1] ) ){
      return asccode[scancode][1];
    }
    // si llega aca es porque esta con bloqmayus pero no tocando una letra, en cuyo caso debo ignorar este flag, 
    // o porque no está tocando la mayus, asi q solo me falta comprobar el shift
    return asccode[scancode][pressingShift]; 
  }
  return -1;
}

char getKeyPressed(){
    int scanCode = getScanCode();
    char c;
    if(scanCode == ESC_SCANCODE) {
      c = ESC_ASCII;
    } else if(scanCode == ALT_SCAN_CODE) {
      c = CAPTURE_FLAGS;
    } else if(codeMatchesAscii(scanCode) && !pressingCtrl){
      return getMatchingAscii(scanCode);
    } else {
      return -1;
    }
}