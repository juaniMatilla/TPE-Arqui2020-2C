
#include "idt.h"

DESCR_INT * idt = (DESCR_INT *) 0;	// IDT de 255 entradas

static void setup_IDT_entry (int index, uint64_t offset);
//void _int80Handler(uint64_t num, const char* buff); //modificar no esta bien asi



void load_idt() {

    setup_IDT_entry (0x00, (uint64_t)&_ex00Handler);
    setup_IDT_entry (0x01, (uint64_t)&_ex01Handler);

    setup_IDT_entry (0x20, (uint64_t) &_irq00Handler); //timer tick
    setup_IDT_entry (0x21, (uint64_t) &_irq01Handler); //keyboard
    
    setup_IDT_entry (0x80, (uint64_t) &_irq80Handler); 
    setup_IDT_entry (0x81, (uint64_t) &_irq81Handler);

	//timer tick y teclado habilitadas
    picMasterMask(0xFC); 
	picSlaveMask(0xFF);
        
	_sti();
}

void exDispatcher(uint64_t num, uint64_t *RIP, uint64_t *RSP){
    switch(num){
		case 0: 
				writeConsole("ZERO EXCEPTION \n" );
            break;
	    case 1: 
				writeConsole("INVALID OPERATION CODE \n");
		    break;
	}
	printRegister( saveRegisters(RSP, RIP) );

}

void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0: 
            //testerTick();
			break;
        case 1: // Keyboard
            keyboard_handler();
            break;
        case 8: //RTC int
            //purebaRTC();
            break;
	}
	return;
}

void int80Handler(uint64_t num, uint64_t *RSP) {
   //se cuenta desde el r15 como 0 hasta rax en el orde de popState 
   // rdi -> RSP[9], rsi -> RSP[8]
    switch (num) {
        case 0:
            writeConsole(RSP[9]);
            break;
        case 1:
            writeCharConsole(RSP[9]);
            break;
        case 2:
            setConsoleSize(RSP[9], RSP[8] , RSP[11], RSP[12]);
            break;
        case 3: 
            drawFont16x16(RSP[9], RSP[8] , RSP[11], RSP[12], RSP[7], RSP[6]);
            break;
        case 4:
            clearDisplay(RSP[9]);
            break;
        case 5:
            readStandardInput(RSP[9], RSP[8]);
            break;
        case 6:
            KBsize(RSP[9]);
            break;
        case 7:
            backspace();
            break;
        case 8:
            getDataTime(RSP[9], RSP[8]);
            break;
        case 10:
            getFromAdress(RSP[9], RSP[8]);
            break;
	}
	return;
}

uint64_t* int81Handler(uint64_t *RIP, uint64_t *RSP){
    return saveRegisters(RSP, RIP);
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