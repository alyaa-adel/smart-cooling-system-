#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "MCAL/ADC/ADC.h"
#include "HAL/LCD/LCD.h"

#define F_CPU160000000
#define TEMP_SENSOR_PIN 2 
#define FAN_PIN PD6

volatile uint16_t timeCounter = 0;

int main(void)
{
    
    ADC_init();
  
    // Initialize Timer0 for PWM(responsible for active led , better for motors )
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);//mode clear on match  and fast pwm
   // OCR0A = (unsigned char)(0.5*255);
	TCCR0B |= (1 << CS00);//prescalar clk/1-->16MHZ
   
    DDRD |= (1 << FAN_PIN);
	
    // Initialize Timer1 for interrupt(auto turn off)
    TCCR1B |= (1 << WGM12);       // Set Timer1 in CTC mode
    TCCR1B |= (1 << CS11) | (1 << CS10); // Set prescaler to 64
    OCR1A = 15625;       // Set compare value for 1 second at 16 MHz(1*10^6)/64
    TIMSK1 |= (1 << OCIE1A);      // Enable Timer1 
    sei();  // Enable global interrupts

    // Initialize the LCD
  
    LCD_DDR = 0xFF; // Set PORTB as output

    _delay_ms(20); // Wait before LCD activation
    LCD_Command(0x02); // 4-Bit Control
    LCD_Command(0x28); // Control Matrix @ 4-Bit
    LCD_Command(0x0C); // Disable Cursor
    LCD_Command(0x06); // Move Cursor
    LCD_Command(0x01); // Clear LCD
    _delay_ms(2);
    
    // Main loop
    while (1) 
    {
        // Read temperature from ADC
        //ADCSRA |= (1 << ADSC);
        //while (ADCSRA & (1 << ADSC));
        uint8_t tempValue = ADC_read(2);
		
        float temperature =( tempValue *(5.0 / 256.0) * 100.0) ;

        // Control the fan
        if (temperature > 30)
        {
            OCR0A = (unsigned char)(((temperature-30.0)/(40.0-30.0))*255);   //timer 0 =8bits so 2^8
        }
        else
        {
            OCR0A = 0;
        }

        // Display temperature on LCD
        LCD_Clear();
        uint16_t tempInt = (uint16_t)temperature; // Convert float to integer
        char tempMessage[16]; // Assuming 16 characters is enough for the temperature message
        sprintf(tempMessage, "Temp.: %d", tempInt); // Print integer part and two decimal places
        LCD_Print(tempMessage);
        
        _delay_ms(1000);  // Wait for 1 second
    }
    return 0;
}
//auto turun off
ISR(TIMER1_COMPA_vect) // when OCR1A= TCNT1
{
    timeCounter++;           
    if (timeCounter >= 5)     // when trun 5 the fan will be off 
    {
        OCR0A = 0; 
        PORTD &= ~(1 << FAN_PIN); // Turn off fan by clearing the FAN_PIN bit
        timeCounter = 0;          // Reset
    }
}


