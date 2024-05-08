#include "main.h"

void fastPwmTim0(uint8_t dutyCycle)
{
	// Setup
	DDRD   |= (1<<PORTD6);
	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM mode, non-inverting
	TCCR0B = (1 << CS01) | (1 << CS00);					  // Prescaler = 64
	// Set the initial duty cycle (0 to 255)
	OCR0A = 255*((float)dutyCycle/100.00);
}
