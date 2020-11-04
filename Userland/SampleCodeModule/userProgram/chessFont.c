//funcion que le pasa char y me devuelve un puntero al vector en el char en guiones y cruces
#ifndef FONT_BITMAPS_H
#define FONT_BITMAPS_H

#include "chessFont.h"

static unsigned char __font_bitmap__[] = {
	//EMPTY
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	________,________,
	//	KING
	_______X,X_______,
	_____XXX,XXX_____,
	_______X,X_______,
	______XX,XX______,
	_____X__,__X_____,
	___XXXXX,XXXXX___,
	___X____,____X___,
	____XXXX,XXXX____,
	______X_,_X______,
	_____X__,__X_____,
	_____X__,__X_____,
	____X___,___X____,
	____X___,___X____,
	___XXXXX,XXXXX___,
	__X_____,_____X__,
	_XXXXXXX,XXXXXXX_,
	//QUEEN
	_______X,X_______,
	_____XXX,XXX_____,
	____X__X,X__X____,
	____X___,___X____,
	_____X__,__X_____,
	___XXXXX,XXXXX___,
	___X____,____X___,
	____XXXX,XXXX____,
	______X_,_X______,
	_____X__,__X_____,
	_____X__,__X_____,
	____X___,___X____,
	____X___,___X____,
	___XXXXX,XXXXX___,
	__X_____,_____X__,
	_XXXXXXX,XXXXXXX_,
	// KNIGHT
 	_____XXX,_XXX____,
	____XXXX,_XXXX___,
	___X____,__XXX___,
	__X___X_,__XXXX__,
	__X_____,__XXXX__,
	__X_____,___XXXX_,
	__XXXX__,____XXX_,
	______X_,____XXX_,
	______X_,____XXX_,
	_____X__,___XXX__,
	____X___,__XXXX__,
	____X___,__XXX___,
	___XXXXX,XXXXX___,
	__X_____,_____X__,
	_X______,______X_,
	_XXXXXXX,XXXXXXX_,
    //ROOK
	___XX__X,X__XX___,
	__X__XX_,_XX__X__,
	__X_____,_____X__,
	__X_____,_____X__,
	___XXXXX,XXXXX___,
	____X___,___X____,
	____X___,___X____,
	____X___,___X____,
	____X___,___X____,
	____X___,___X____,
	____X___,___X____,
	____X___,___X____,
	___XXXXX,XXXXX___,
	__X_____,_____X__,
	_X______,______X_,
	_XXXXXXX,XXXXXXX_,
    // BISHOP
	_______X,X_______,
	______XX,XX______,
	_____XX_,_XX_____,
	____XX__,__XX____,
	___XXXXX,XXXXX___,
	___X____,____X___,
	____X___,___X____,
	_____XXX,XXX_____,
	______X_,_X______,
	______X_,_X______,
	_____X__,__X_____,
	____X___,___X____,
	____X___,___X____,
	___XXXXX,XXXXX___,
	__X_____,_____X__,
	_XXXXXXX,XXXXXXX_,
    // PAWN
	_______X,X_______,
	______X_,_X______,
	______X_,_X______,
	____XXXX,XXXX____,
	____X___,___X____,
	_____XXX,XXX_____,
	______X_,_X______,
	______X_,_X______,
	______X_,_X______,
	______X_,_X______,
	_____X__,__X_____,
	____X___,___X____,
	____X___,___X____,
	___XXXXX,XXXXX___,
	__X_____,_____X__,
	_XXXXXXX,XXXXXXX_
};

unsigned char* charBitmap(int num) {
	return (__font_bitmap__+(num)*(CHAR_HEIGHT+CHAR_WIDTH));
}

#endif