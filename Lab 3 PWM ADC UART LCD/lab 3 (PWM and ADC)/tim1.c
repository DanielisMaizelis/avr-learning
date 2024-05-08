#include "main.h"


void fastPwmTim1(uint8_t dutycycle)
{
	DDRB |= (1 << PORTB1);
	// Configure Timer 1 for Fast PWM mode with ICR1 as TOP
	TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Clear OC1A on compare match, set OC1A at BOTTOM
	TCCR1B |= (1 << WGM13) | (1 << WGM12);  // Fast PWM mode with ICR1 as TOP
	TCCR1B |= (1 << CS11)|(1 << CS10);		 // Set prescaler to 8

	// Set ICR1 to define the PWM period
	ICR1 = 1000;

	// Optionally, set OCR1A to define the initial PWM duty cycle
	OCR1A = dutycycle*10;
}