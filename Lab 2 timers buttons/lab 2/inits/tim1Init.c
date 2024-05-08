#include "../main.h"



void setupTim1Polling(void) // Task 1
{
	TCCR1B = (1<<CS12)| (1<<CS10) ; // Prescaler
	TCNT1 = 0;						// Counter starts from 0
}

void setupTim1Irq(void) // Task 2
{
	TCNT1  = 0;							 //initialize counter value to 0
	OCR1A = 31249;                       // 2*((16*10^6)/1024)-1 -> 2 Sec delay (value must be <65536)
	TCCR1B |= (1 << WGM12);				 // turn on CTC mode
	TCCR1A |= (1 << COM1A0);			 // Pin mode CTC
	TCCR1B |= (1 << CS12) | (1 << CS10); // Set CS12 and CS10 bits for 1024 prescaler
	TIMSK1 |= (1 << OCIE1A);			 // enable timer compare interrupt
}

void pollTim1Blink(void) // Task 1
{
	if(TCNT1 >= POLLING_MODE_1SEC)
	{
		PORTB ^= (1<<PORTB0);
		TCNT1 = 0;
	}
}