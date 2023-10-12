
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Cfg.h"
#include "Utils.h"

#define F_CPU  8000000
#include <util/delay.h>

#if LCD_MODE==_8_BIT

static void WriteIns(u8 ins){
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data){
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void){
	_delay_ms(50);
	WriteIns(0x38);
	WriteIns(0x0F); //0x0C,0x0E,0x0F
	WriteIns(0x01); //clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

#else

static void WriteIns(u8 ins){
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data){
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void){
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0C); //0x0C,0x0E,0x0F
	WriteIns(0x01); //clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

#endif

void LCD_Clear(void){
	WriteIns(0x01); //clear screen
	_delay_ms(1);
}

void LCD_GoTo(u8 line, u8  cell){
	if(line==0){
		WriteIns(0x80+cell);
	}
	else if(line==1){
		WriteIns(0x80+0x40+cell);
	}
}

void LCD_WriteChar(u8 ch){
	WriteData(ch);
}

void LCD_WriteString(c8 *str){
	u8 i;
	for(i=0;str[i];i++){
		LCD_WriteChar(str[i]);
	}
}

void LCD_WriteNumber(s32 num){
	u8 str[20];
	u8 i=0;
	s8 j;
	if(num<0){
		LCD_WriteChar('-');
		num*=-1;
	}
	if(num==0){
		LCD_WriteChar('0');
		return;
	}
	while(num){
		str[i]=num%10+'0';
		i++;
		num=num/10;
	}
	for(j=i-1;j>=0;j--){
		LCD_WriteChar(str[j]);
	}
}

void LCD_Write_4D(u16 num){
	LCD_WriteChar((num%10000)/1000+'0'); //31206
	LCD_WriteChar((num%1000)/100+'0');
	LCD_WriteChar((num%100)/10+'0');
	LCD_WriteChar((num%10)/1+'0');
}

void LCD_WriteBinary(u8 num){
	s8 i;
	for(i=7;i>=0;i--){
		//LCD_WriteChar(READ_BIT(num,i)?'1':'0');
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}

void LCD_WriteHex(u8 num){
	u8 i=1,j,temp;
	c8 hex[10];
	if(num==0){
		LCD_WriteString("0 ");
		return;
	}
	while(num!=0){
		temp=num%16;
		if(temp<10){
			temp=temp+'0';
		}
		else{
			temp=temp-10+'A';
		}
		hex[i++]=temp;
		num/=16;
	}
	for(j=i-1;j>0;j--){
		LCD_WriteChar(hex[j]);
	}
}

void LCD_WriteStringGoto(u8 line, u8 cell, c8 *str){
	LCD_GoTo(line,cell);
	LCD_WriteString(str);
}

void LCD_ClearPosition(u8 line, u8 cell, u8 NoCells){
	LCD_GoTo(line,cell);
	for(u8 i=0;i<NoCells;i++){
		LCD_WriteChar(' ');
	}
}

void LCD_CustomChar(u8 address, u8 *pattern){
	WriteIns(0x40+address*8);
	for(u8 i=0;i<8;i++){
		WriteData(pattern[i]);
	}
	WriteIns(0x80);
}