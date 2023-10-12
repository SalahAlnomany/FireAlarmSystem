
#ifndef FIREALARM_H_
#define FIREALARM_H_


void FireAlarm_Init(void);
void FireAlarm_Runnable(void);

#define GREEN_LED   PINC1
#define YELLOW_LED  PINC2
#define RED_LED     PINC3
#define MOTOR_EN    PINC0


#endif /* FIREALARM_H_ */