#define F_CPU 16000000UL
#include <avr/io.h>


// Interrupts:





int main(void)
{
	// Setup Pins:
	PORTB		   |= 0b00000000;
	DDRB		   |= 0b00000000;
	uint8_t value1	= 0b00010000;
	
	// Turn an LED on:
	DDRB |= value1;
	
	
    while (1) 
    {
		// Blink the LED:
		
		
		
		
    }
}



