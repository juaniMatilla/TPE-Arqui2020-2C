
#include "idt.h"
#include <stdarg.h> //permite arumentos variables

#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de interrupcion */
typedef struct {
  uint16_t offset_l;
  uint16_t selector;
  uint8_t cero;
  uint8_t access;
  uint16_t offset_m;
  uint32_t offset_h;
  uint32_t other_cero;
} DESCR_INT;

DESCR_INT * idt = (DESCR_INT *) 0;	// IDT de 255 entradas

//private:
static void setup_IDT_entry (int index, uint64_t offset);
void _int80Handler(uint64_t num, const char* buff); //modificar no esta bien asi


void load_idt() {

    //setup_IDT_entry (0x00, (uint64_t)&_ex00Handler);

    setup_IDT_entry (0x20, (uint64_t) &_irq00Handler); //timer tick
    setup_IDT_entry (0x21, (uint64_t) &_irq01Handler); //keyboard
    
    setup_IDT_entry (0x80, (uint64_t) &_irq80Handler); 
    //setup_IDT_entry (0x80, (uint64_t)&_irq80Handler01); 

	//timer tick y teclado habilitadas
    picMasterMask(0xFC); 
	picSlaveMask(0xFF);
        
	_sti();
}

/*void writeIDT(){
    _cli();

    setup_IDT_entry (0x0, (uint64_t)&_ex00Handler);  // DivByZero
    setup_IDT_entry (0x6, (uint64_t)&_ex06Handler);  // InvalidOpCode

    setup_IDT_entry (0x20, (uint64_t)&_irq00Handler); //DivByZero
    timer_Restart(); // Inicializa el timer_Tick

    setup_IDT_entry (0x21, (uint64_t)&_irq01Handler); 
    setup_IDT_entry (0x28, (uint64_t)&_irq08Handler);  //RTC int 
    
    setup_IDT_entry (0x80, (uint64_t)&_int80handler); 

    //habilita 1y2 (Timer_Tick y teclado)
    picMasterMask(0xFC); 
	picSlaveMask(0x00);

    // configuracion frecuencia PIC
    //int hz = PIT_FREQUENCY;
    //int divisor = 1193180 / hz;
    //outportb(PIT_CMDREG, 0x36);
    //outportb(PIT_CHANNEL0, divisor & 0xFF);
    //outportb(PIT_CHANNEL0, divisor >> 8);

    _sti();
}*/


void exDispatcher(uint64_t ex){
    //falta hacer
}
//cambiar el switch por un vector de punteros a funcion
void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0: //Timer_Tick
            //testerTick();
			break;
        case 1: // Keyboard
            testerkeyboard();
            //kb_fetch();
            break;
        case 8: //RTC int
            //purebaRTC();
            break;
	}
	return;
}

void int80Handler(uint64_t num, ...) {
    va_list ap;
    va_start(ap, num);

    switch (num) {
        case 1:
            print(va_arg(ap, int));
            print("   ");

            break;
        case 2: 
            redPrint(va_arg(ap, int));
            print("   ");
            break;
	}
	return;
}


static void setup_IDT_entry (int index, uint64_t offset) {
    idt[index].offset_l = offset & 0xFFFF;  
    idt[index].selector = 0x08;
    idt[index].cero = 0;
    idt[index].access = ACS_INT;
    idt[index].offset_m = (offset >> 16) & 0xFFFF;
    idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
    idt[index].other_cero = (uint64_t) 0;
}