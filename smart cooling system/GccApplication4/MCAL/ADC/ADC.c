/*
 * ADC.c
 *
 * Created: 5/29/2024 10:14:15 PM
 *  Author: Rana
 */ 
#include <avr/io.h>
#include "ADC.h"
#include "../../LIBRARY/BITMATH.h"

void ADC_init()

{   
	SET_BIT(ADMUX,REFS0); // VCC
	// Prescaler 64
	SET_BIT(ADCSRA,ADPS1); 
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADEN);  // Enable ADC
	//SET_BIT(ADMUX,MUX1); // Select channel
	SET_BIT(ADMUX,ADLAR);   // Left adjust ADC result
	
	
	
}

uint16_t ADC_read(uint8_t ch)
{
	ch &= 0b00000111; // Select ADC channel ch must be 0-7
	ADMUX = (ADMUX & 0xF8) | ch; // Clear last 3 bits and set channel
	SET_BIT(ADCSRA,ADSC); // Start single conversion
	while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete
	return ADCH;
}
