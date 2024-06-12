/*
 * LCD.h
 *
 * Created: 5/29/2024 10:21:31 PM
 *  Author: Rana
 */ 


#ifndef LCD_H_
#define LCD_H_
#include <avr/io.h>
#include <util/delay.h>

// LCD control and data ports
#define LCD_DATA_PORT PORTB
#define LCD_DDR DDRB
#define LCD_RS PB0
#define LCD_E PB1
#define LCD_DATA_MASK 0xF0 // We will use PB4-PB7 for data lines
#define  fourBit_Control         0x02
#define  Control_MatrixatfourBit 0x28
#define  Disable_Cursor			 0x0C
#define  Move_Cursor			 0x06
#define  Clear_LCD				 0x01
	



// Function prototypes for LCD
void LCD_Init(void);
void LCD_Command(unsigned char cmnd);
void LCD_Clear(void);
void LCD_Print(char *str);
void LCD_SetCursor(unsigned char row, unsigned char column);




#endif /* LCD_H_ */