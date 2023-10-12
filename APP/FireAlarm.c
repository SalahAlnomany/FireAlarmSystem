
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "ADC_Interface.h"
#include "Sensors_Interface.h"
#include "FireAlarm.h"


static u16 str_length(u8 *str);
static u16 pass_check(u8 *str1, u8 *str2);

void FireAlarm_Init(void){
	
	DIO_Init();
	ADC_Init(VREF_AVCC,ADC_SCALER_64);
	LCD_Init();
	KEYPAD_Init();
	
	LCD_GoTo(0,6);
	LCD_WriteString("Fine");
	
	DIO_WritePin(GREEN_LED,HIGH);
	DIO_WritePin(YELLOW_LED,LOW);
	DIO_WritePin(RED_LED,LOW);
	DIO_WritePin(MOTOR_EN,LOW);
}

void FireAlarm_Runnable(void){
	
	u16 temp=0,smoke=0;
	u8 i=0,reset_flag=1,enter_flag=0;
	
	u8 reset_pass[]="12345";
	u8 enter_pass[10];
	
	temp=TEMP_Read();
	temp/=10;
	
	LCD_GoTo(1,0);
	LCD_WriteNumber(temp);
	LCD_WriteString("-C ");
	
	if(temp>50){
		smoke=PRESS_Read();
		
		LCD_GoTo(1,12);
		LCD_WriteNumber(smoke);
		LCD_WriteString("   ");
		
		if(smoke>650){
			LCD_GoTo(0,6);
			LCD_WriteString("Fire");
			
			DIO_WritePin(GREEN_LED,LOW);
			DIO_WritePin(YELLOW_LED,LOW);
			DIO_WritePin(RED_LED,HIGH);
			DIO_WritePin(MOTOR_EN,HIGH);
			
			LCD_GoTo(1,0);
			LCD_WriteString(" Pass to reset! ");
			
			reset_flag=1;
			
			while(reset_flag){
				u8 k=KEYPAD_GetKey();
				
				if(k!=NO_KEY){
					if(k>='0'&&k<='9'){
						if(i==0){
							LCD_GoTo(1,0);
							LCD_WriteString("                  ");
							LCD_GoTo(1,0);
						}
						LCD_WriteChar(k);
						enter_pass[i]=k;
						i++;
					}
					else if(k=='='){
						enter_flag=1;
					}
					else if(k=='C'&&i!=0){
						LCD_GoTo(1,0);
						LCD_WriteString("                  ");
						LCD_GoTo(1,0);
						i=0;
					}
				}
				if(pass_check(reset_pass,enter_pass)==0&&enter_flag==1){
					LCD_GoTo(1,0);
					LCD_WriteString("Wrong Password!");
					enter_flag=0;
					reset_flag=1;
					i=0;
				}
				else if(pass_check(reset_pass,enter_pass)==1&&enter_flag==1){
					enter_flag=0;
					reset_flag=0;
					i=0;
				}
			}

		}
		else{
			LCD_GoTo(0,6);
			LCD_WriteString("Heat");
			
			DIO_WritePin(GREEN_LED,LOW);
			DIO_WritePin(YELLOW_LED,HIGH);
			DIO_WritePin(RED_LED,LOW);
			DIO_WritePin(MOTOR_EN,LOW);
		}
	}
	else if(temp<45){
		LCD_GoTo(0,6);
		LCD_WriteString("Fine");
		
		LCD_GoTo(1,12);
		LCD_WriteString("    ");
		
		DIO_WritePin(GREEN_LED,HIGH);
		DIO_WritePin(YELLOW_LED,LOW);
		DIO_WritePin(RED_LED,LOW);
		DIO_WritePin(MOTOR_EN,LOW);
	}
}
	

static u16 str_length(u8 *str){
	u16 i;
	for(i=0; str[i]; i++);

	return i;
}

static u16 pass_check(u8 *str1, u8 *str2){
	u16 i;
	
	if(str_length(str1)!=str_length(str2)){
		return 0;
	}
	for(i=0;i<str_length(str1);i++)
	{
		if(str1[i]!=str2[i])
		{
			return 0;
		}
	}
	return 1;
}