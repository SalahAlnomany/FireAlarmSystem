
#include "StdTypes.h"
#include "ADC_Interface.h"
#include "Sensors_Cfg.h"
#include "Sensors_Interface.h"


u16 Interpolation(u16 y1, u16 y2, u16 x1, u16 x2, u16 p){
	
	return (((u32)(y2-y1)*(p-x1))/(x2-x1))+y1;
}

u16 TEMP_Read(void){
	u16 volt;
	u16 temp;
	volt=ADC_VoltRead(LM35_CH);
	temp=volt;
	return temp;
}

u16 PRESS_Read(void){
	u16 adc;
	u16 press;
	adc=ADC_Read(MPX4115_CH);
	//press=((((u32)1000*(adc-55))+460)/921)+150; //interpolation
	press=Interpolation(150,1150,55,976,adc);
	return press;
}

/*
u8 POT_Read(void){
	
}*/