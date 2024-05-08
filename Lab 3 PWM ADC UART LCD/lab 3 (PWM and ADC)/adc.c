#include "main.h"


void adcSetup()
{
	DDRC   |= 0x00;					  // Set the pins for analog as input
	PORTC  |= 0x00;			          // Set the pins for analog as input
	ADCSRA |= (1 << ADEN) | (1 << ADIE)| (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, ADC Interrupt
	ADMUX  |= 1 << REFS0;				  // Set reference voltage to AVCC
	// ADMUX  |= 1 << ADLAR;				  // Left adjust result

	// Set ADC channel to 0
	//ADMUX &= ~(1 << MUX0) & ~(1 << MUX1) & ~(1 << MUX2) & ~(1 << MUX3);
	ADMUX |= (1 << MUX0);

	// Start conversion and interrupts
	ADCSRA |= (1 << ADSC)|(1<< ADIE);
}