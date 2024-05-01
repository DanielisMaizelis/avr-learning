#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t result;

ISR(ADC_vect)
{
	result = ADC;
}

void fastPwmTim1()
{
	 DDRB |= (1 << DDB1);
	 // Configure Timer 1 for Fast PWM mode with ICR1 as TOP
	 TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Clear OC1A on compare match, set OC1A at BOTTOM
	 TCCR1B |= (1 << WGM13) | (1 << WGM12); // Fast PWM mode with ICR1 as TOP
	 TCCR1B |= (1 << CS11)|(1 << CS10);		// Set prescaler to 8

	 // Set ICR1 to define the PWM period
	 ICR1 = 1000; 

	 // Optionally, set OCR1A to define the initial PWM duty cycle
	 OCR1A = 100; 
}

void phCorrPwmTim1()
{
	DDRB |= (1 << PORTB1);
	// Set Phase Correct PWM mode with non-inverting output on OC1A (Pin PB1)
	TCCR1A |=  (1 << COM1A1) | (1 << WGM11);
	// Set WGM13, CS10, and CS12 bits for Phase Correct PWM mode with prescaler 64
	TCCR1B |= (1 << WGM13) | (1 << CS10) | (1 << CS11);
	
	// Set ICR1 to define the PWM period
	ICR1 = 1000; 

	// Optionally, set OCR1A to define the initial PWM duty cycle
	OCR1A = 900; 
}


void fastPwmTim0()
{
	DDRD   |= (1<<PORTD6);
	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM mode, non-inverting
	TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler = 64
 
	// Set the initial duty cycle (0 to 255)
	OCR0A = 127; // 50% duty cycle
}


void adcSetup()
{
	//Ch 0 set
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADIE);
	// ADLAR is 0, so little endian
}

int main(void)
{
	// Set PB1 (OC1A) as output for PWM
	// Initialize PWM in Fast PWM mode
	//fastPwmTim1();

	// Or Initialize PWM in Phase Correct PWM mode
	phCorrPwmTim1();
	fastPwmTim0();
	sei();
	while (1)
	{
		
		// Your main loop code
	}

	return 0;
}
