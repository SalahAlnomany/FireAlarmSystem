
#define  KEYPAD_PRG  1

#include "StdTypes.h"
#include "DIO_Interface.h"
#include "KeyPad_Interface.h"
#include "KeyPad_Cfg.h"
#include "Utils.h"


void KEYPAD_Init(void){
	for(u8 r=0;r<ROWS;r++){
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
}

u8 KEYPAD_GetKey(void){
	u8 r,c,key=NO_KEY;
	for(r=0;r<ROWS;r++){
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		for(c=0;c<COLS;c++){
			if(DIO_ReadPin(FIRST_INPUT+c)==LOW){
				key=KeyArr[r][c];
				DEBOUNCING_DELAY;
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
				DEBOUNCING_DELAY;
			}
		}
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
	return key;
}