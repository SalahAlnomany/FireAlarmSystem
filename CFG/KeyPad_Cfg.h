


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define  ROWS   4
#define  COLS   4

#define  NO_KEY  'T'

#define  FIRST_OUTPUT   PINB4
#define  FIRST_INPUT    PIND2

#if KEYPAD_PRG

u8 KeyArr[ROWS][COLS]={{'7','8','9','/'},
					   {'4','5','6','*'},
					   {'1','2','3','-'},
					   {'C','0','=','+'}};			   
#endif



#endif /* KEYPAD_CFG_H_ */