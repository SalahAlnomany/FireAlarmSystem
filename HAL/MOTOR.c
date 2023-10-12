
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Cfg.h"


/************************************************IN1    IN2*/
static DIO_Pin_type MotorPinsArr[MOTORS][PINS]={{M1_IN1,M1_IN2}, /*M1*/
												{M2_IN1,M2_IN2}, /*M2*/
												{M3_IN1,M3_IN2}, /*M3*/
												{M4_IN1,M4_IN2}};/*M4*/
												   
//typedef struct{
	//DIO_Pin_type IN1;
	//DIO_Pin_type IN2;
//}MOTOR_Pin_type;
												   //
///************************************************IN1    IN2*/
//static MOTOR_Pin_type MotorPinsArr2[MOTORS]={{M1_IN1,M1_IN2}, /*M1*/
										   //{M2_IN1,M2_IN2}, /*M2*/
										   //{M3_IN1,M3_IN2}, /*M3*/
										   //{M4_IN1,M4_IN2}};/*M4*/

void MOTOR_Init(void){
	
}

void MOTOR_Stop(MOTOR_type m){
	DIO_WritePin(MotorPinsArr[m][IN1],LOW);
	DIO_WritePin(MotorPinsArr[m][IN2],LOW);
	/*
	DIO_WritePin(MotorPinsArr2[m].IN1,LOW);
	DIO_WritePin(MotorPinsArr2[m].IN2,LOW);*/
	
	/*switch(m){
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,LOW);
		break;
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,LOW);
		break;
		case M3:
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,LOW);
		break;
		case M4:
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,LOW);
		break;
	}*/
}

void MOTOR_CW(MOTOR_type m){
	DIO_WritePin(MotorPinsArr[m][IN1],LOW);
	DIO_WritePin(MotorPinsArr[m][IN2],HIGH);
	/*switch(m){
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,HIGH);
		break;
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,HIGH);
		break;
		case M3:
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,HIGH);
		break;
		case M4:
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,HIGH);
		break;
	}*/
}

void MOTOR_CCW(MOTOR_type m){
	DIO_WritePin(MotorPinsArr[m][IN1],HIGH);
	DIO_WritePin(MotorPinsArr[m][IN2],LOW);
	/*switch(m){
		case M1:
		DIO_WritePin(M1_IN1,HIGH);
		DIO_WritePin(M1_IN2,LOW);
		break;
		case M2:
		DIO_WritePin(M2_IN1,HIGH);
		DIO_WritePin(M2_IN2,LOW);
		break;
		case M3:
		DIO_WritePin(M3_IN1,HIGH);
		DIO_WritePin(M3_IN2,LOW);
		break;
		case M4:
		DIO_WritePin(M4_IN1,HIGH);
		DIO_WritePin(M4_IN2,LOW);
		break;
	}*/
}

void MOTOR_Speed(MOTOR_type m, u8 speed){
	if(speed>MOTOR_MAX_SPEED){
		speed=MOTOR_MAX_SPEED;
	}
}