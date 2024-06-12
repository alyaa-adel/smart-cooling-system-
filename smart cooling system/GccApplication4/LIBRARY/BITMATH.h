/*
 * BITMATH.h
 *
 * Created: 5/29/2024 10:41:25 PM
 *  Author: Rana
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_


#define SET_BIT(Port_ID,Pin_ID)     ((Port_ID) |=     (1<<(Pin_ID)))
#define CLEAR_BIT(Port_ID,Pin_ID)    ((Port_ID) &= (~ (1<<(Pin_ID))))
#define TOOGLE_BIT(Port_ID,Pin_ID)    ((Port_ID) ^=     (1<<(Pin_ID)))
#define GET_BIT(Port_ID,Pin_ID)        (((Port_ID)>>(Pin_ID)) &(0x01))


#endif /* BITMATH_H_ */