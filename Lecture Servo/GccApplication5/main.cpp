/*
 * GccApplication5.cpp
 *
 * Created: 22/09/2022 10:48:44
 * Author : Maizel
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int time_delay = 0;
volatile uint16_t Overflows;



ISR(TIMER0_OVF_vect)
{
	Overflows++;
	if((PINC & 0x01) == 0x01) // If the output is high
	{
		if(Overflows >= (62*time_delay)) // 1 or 2 ms has elapsed
		{
			PORTC &= ~(1<<PORTC0); // Turn the output low
		}
	}
	if((PINC & 0x01) == 0x00)  // If the output is low
	{
		if(Overflows >= (1249)) // 20 ms has elapsed
		{
			PORTC |= (1<<PORTC0); // Turn the output high
			Overflows = 0; // Reset overflows
		}
	}
	
}


void setServoMax()
{
	time_delay = 2;
}

void setServoMin()
{
	time_delay = 0;
}

int main(void)
{
	DDRC = 0b11111111;
	//DDRB = 0b00000001;
	
	
	// Timer 0 for my servo
	TCNT0 = 0;
	TCCR0B |= (1<<CS00);
	TIMSK0 |= (1<<TOIE0);
	
	// Timer 1 for calculating the time
	TCNT0 = 0;
	TCCR0B |= (1<<CS00);
	TIMSK0 |= (1<<TOIE0);
	
	sei();
    while (1) 
    {
		setServoMax();
		_delay_ms(1000);
		setServoMin();
		_delay_ms(1000);
    }
}

