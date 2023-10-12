

#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_


u16 Interpolation(u16 y1, u16 y2, u16 x1, u16 x2, u16 p);

/* return temp cel*10 */
u16 TEMP_Read(void);

u16 PRESS_Read(void);

u8 POT_Read(void);


#endif /* SENSORS_INTERFACE_H_ */