/*
 * LCD.c
 *
 * Created: 5/29/2024 10:21:46 PM
 *  Author: Rana
 */ 
#include "LCD.h"
void LCD_Init(void)
{
	LCD_DDR = 0xFF; // Set PORTB as output

	_delay_ms(20); // Wait before LCD activation
	LCD_Command( fourBit_Control        ); 
	LCD_Command( Control_MatrixatfourBit); 
	LCD_Command( Disable_Cursor			); 
	LCD_Command( Move_Cursor			); 
	LCD_Command( Clear_LCD				); 
	_delay_ms(2);
}

void LCD_Command(unsigned char cmnd)
{
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmnd & 0xF0); // Send higher nibble
	PORTB &= ~(1 << LCD_RS); // RS = 0 for command
	PORTB |= (1 << LCD_E); // Enable pulse
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);

	_delay_us(200);

	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmnd << 4); // Send lower nibble
	PORTB |= (1 << LCD_E); // Enable pulse
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);

	_delay_ms(2);
}

void LCD_Clear(void)
{
	LCD_Command(0x01); // Clear LCD
	_delay_ms(2); // Wait to clear LCD
	LCD_Command(0x80); // Move to Position Line 1, Position 1
}

void LCD_Print(char *str)
{
	while (*str)
	{
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (*str & 0xF0); // Send higher nibble
		PORTB |= (1 << LCD_RS); // RS = 1 for data
		PORTB |= (1 << LCD_E); // Enable pulse
		_delay_us(1);
		PORTB &= ~(1 << LCD_E);

		_delay_us(200);

		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (*str << 4); // Send lower nibble
		PORTB |= (1 << LCD_E); // Enable pulse
		_delay_us(1);
		PORTB &= ~(1 << LCD_E);

		_delay_ms(2);
		str++;
	}
}

void LCD_SetCursor(unsigned char row, unsigned char column)
{
	unsigned char pos[] = {0x80, 0xC0};
	LCD_Command(pos[row] + column);
}
