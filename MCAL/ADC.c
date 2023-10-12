
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Interface.h"

static u8 ADC_BusyFlag;

void ADC_Init(ADC_VoltRef_type vref, ADC_Prescaler_type scaler){
	/* vref */\
	switch(vref){
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	/* prescaller */
	ADCSRA&=0xF8;
	scaler&=0x07;
	ADCSRA|=scaler;
	
	/* enable ADC */
	SET_BIT(ADCSRA,ADEN);
}

u16 ADC_Read(ADC_Channel_type ch){
	/* set channel mux */
	ADMUX&=0xE0;
	ADMUX|=ch;
	
	/* start conversion */
	SET_BIT(ADCSRA,ADSC);
	
	/* wait ADC finish */
	while(READ_BIT(ADCSRA,ADSC));
	
	/* get read */
	/*u16 adc=ADCL;
	adc|=(ADCH<<8);*/
	/* SET_BIT(ADMUX,ADLAR);
	u16	adc=ADCL>>6;
	adc|=(ADCH<<2); */
	return ADC;
}

void ADC_StartConversion(ADC_Channel_type ch){
	if(ADC_BusyFlag==0){
		/* set channel mux */
		ADMUX&=0xE0;
		ADMUX|=ch;
		
		/* start conversion */
		SET_BIT(ADCSRA,ADSC);
		ADC_BusyFlag=1;
	}
}

u16 ADC_GetRead(void){
	
	/* get read */
	/*u16 adc=ADCL;
	adc|=(ADCH<<8);*/
	/* SET_BIT(ADMUX,ADLAR);
	u16	adc=ADCL>>6;
	adc|=(ADCH<<2); */
	
	/* wait ADC finish - busy wait (blocking) */
	while(READ_BIT(ADCSRA,ADSC));
	
	return ADC;
}

u8 ADC_GetReadPeriodic(u16 *pdata){
	/* periodic check (polling) */
	if(!READ_BIT(ADCSRA,ADSC)){
		*pdata=ADC;
		ADC_BusyFlag=0;
		return 1;
	}
	return 0;
}

u16 ADC_VoltRead(ADC_Channel_type ch){
	u16 volt;
	u16 adc;
	adc=ADC_Read(ch);
	volt=((u32)5000*adc)/1024;
	return volt;
}