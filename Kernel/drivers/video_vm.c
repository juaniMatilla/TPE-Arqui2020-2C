
#include "video_vm.h"
//#include "include/console.h"

//se activa desde el bootloder > prue64 > src > sysvar.asm. la costante cfg_vesa en 1 

unsigned int bgColor = 0x0;
unsigned int fColor = 0xFFFFFF;

unsigned int SCREEN_WIDTH = 1024;
unsigned int SCREEN_HEIGHT = 768;
unsigned int SCREEN_BPP= 3;  //los bytes por cada pixel

//contiene todos los datos de la pantalla
struct vbe_mode_info_structure{
    uint16_t attributes;    // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;       // deprecated
    uint8_t window_b;       // deprecated
    uint16_t granularity;   // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;  // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;         // number of bytes per horizontal line
    uint16_t width;         // width in pixels
    uint16_t height;        // height in pixels
    uint8_t w_char;         // unused...
    uint8_t y_char;         // ...
    uint8_t planes;
    uint8_t bpp;   // bits per pixel in this mode
    uint8_t banks; // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer; //puntero al buffer de la memoria de video physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__((packed));

struct  vbe_mode_info_structure * screenData = (void*) 0x5C00; //direccion de memoria donde esta la informacion de modo video

void init_VM_Driver(){
    SCREEN_WIDTH = screenData->width;
    SCREEN_HEIGHT = screenData->height;
    SCREEN_BPP = screenData->bpp / 8;
}

void drawPixel(unsigned int x, unsigned int y, int color){
    char* screen = screenData->framebuffer;
    unsigned where = (x + y*SCREEN_WIDTH) * SCREEN_BPP;
    screen[where] = color & 255; //azul
    screen[where + 1] = (color >> 8) & 255; // verde
    screen[where + 2] = (color >> 16) & 255; // rojo
}

void drawRectangle(unsigned int x, unsigned int y, int b, int h, int color){
    for (int i = 0; i < b; i++)
        for (int j = 0; j < h; j++)
            drawPixel(x+i,y+j,color);
}

void drawSquare(unsigned int x, unsigned int y, int l, int color){
    drawRectangle(x, y, l, l, color);
}

void scrollUp(int cant, unsigned int backgroundColor){
    uint64_t* screen = screenData->framebuffer;

    int i = 0;
    int j = (cant * SCREEN_WIDTH * SCREEN_BPP) / 8;
    while (j < (SCREEN_HEIGHT * SCREEN_WIDTH * SCREEN_BPP) /8){
        screen[i] = screen[j];
        i++;
        j++;
    }
    for (int  i = SCREEN_HEIGHT - cant; i < SCREEN_HEIGHT ; i++)
        for (int  j = 0; j < SCREEN_WIDTH*SCREEN_BPP; j++)
            drawPixel(j,i,backgroundColor);
}

//devulve el ancho del caracter
int drawChar(int x, int y, char character, int fontSize, int fontColor, int backgroundColor){
    int aux_x = x;
    int aux_y = y;
    char bitIsPresent;
    unsigned char* letter = charBitmap(character);

    for (int i = 0; i < CHAR_HEIGHT; i++){
        for (int  j = 0; j < CHAR_WIDTH; j++){
            bitIsPresent = (1 << (CHAR_WIDTH - j)) & letter[i];  //toDraw[i]; //no se que hace buscar
            
            if(bitIsPresent)
                drawSquare(aux_x, aux_y, fontSize, fontColor);
            else
                drawSquare(aux_x, aux_y, fontSize, backgroundColor);
            
            aux_x += fontSize;
        }
        aux_x = x;
        aux_y += fontSize;
    }
    return fontSize*CHAR_WIDTH;
}

void drawString(int x, int y, const char* String, int fontSize, int fontColor, int backgroundColor){
    int aux = 0;
    for (int i = 0; String[i] != 0 ; i++)	{
		drawChar(x+aux, y, String[i], fontSize, fontColor, backgroundColor);
		aux += (CHAR_WIDTH*fontSize);
	}	
}

void clearDisplay(unsigned int backgroundColor){
    char* pos = screenData->framebuffer;
    for (int  i = 0; i < SCREEN_BPP * SCREEN_HEIGHT * SCREEN_WIDTH; i+= SCREEN_BPP){
        pos[i] = backgroundColor & 255; // azul
        pos[i + 1] = (backgroundColor >> 8) & 255; // verde
        pos[i + 2] = (backgroundColor >> 16) & 255; // rojo
    }
}

//usar el mismo sistema que font
void drawMatriz(int x, int y, const char* matriz, int dimx, int dimy, int fontSize, int fontColor, int backgroundColor){
    
    int aux_x = x;
    int aux_y = y;
    char bitIsPresent;

    for (int i = 0; i < dimy; i++){
        for (int  j = 0; j < dimx; j++){
            bitIsPresent = (1 << (dimx - j)) & matriz[i];  //toDraw[i]; //no se que hace buscar
            
            if(bitIsPresent)
                drawSquare(aux_x, aux_y, fontSize, fontColor);
            else
                drawSquare(aux_x, aux_y, fontSize, backgroundColor);
            
            aux_x += fontSize;
        }
        aux_x = x;
        aux_y += fontSize;
    }
    
} 