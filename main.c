/*
 * 
 * FireAlarmSystem.c
 *
 * Author : Salah
 *
 */ 


#include "FireAlarm.h"


int main(void)
{
	FireAlarm_Init();
    while (1) 
    {
		FireAlarm_Runnable();
    }
}

