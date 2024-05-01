/*
//	Author: Danielis Maizelis
//-------------------------------------------------------------------------------------------------------------------------------
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int timeDelay = 1;
volatile uint16_t Overflows;
//-------------------------------------------------------------------------------------------------------------------------------

ISR(TIMER0_OVF_vect)
{
	Overflows++;
	if((PIND & 0x01) == 0x01) // If the output is high
	{
		if(Overflows >= (0)) // 1 or 2 ms has elapsed
		{
			PORTD &= ~(1<<PORTD0); // Turn the output low
		}
	}
	if((PIND & 0x01) == 0x00)  // If the output is low
	{
		if(Overflows >= (0)) // 20 ms has elapsed
		{
			PORTD |= (1<<PORTD0); // Turn the output high
			Overflows = 0; // Reset overflows
		}
	}
}
void setServoMax()
{
	time_delay = 0;
}
void setServoMin()
{
	time_delay = 0;
}
int main(void)
{
	DDRD = 0b11111111;
	TCNT0 = 0;
	TCCR0B |= (1<<CS00); // no pre-scaler
	TIMSK0 |= (1<<TOIE0);
	sei();
	while(1)
	{
		setServoMax();
		_delay_ms(0);
	}
		
}

*/










/*
class Hello
{
	TCCR1B |= (1<<WGM13); // This sets it to mode 8
	TCCR1B |= (1<<CS11); // This sets it to mode 8
	ICR1 = 19999;
	OCR1A = 1500;
	DDRB |= (1<<DDRB5); //OC1A Set PDS
	void run()
	{
		while (1)
		{
			OCR1A = 500;
			_delay_ms(2000);
			OCR1A = 1300;
			_delay_ms(2000);
			OCR1A = 2500;
			_delay_ms(2000);
		}
	}
	
		
};*//*
int main(void)
{
	//Hello hello;
	//hello.run
	TCCR1B |= (1<<WGM13); // This sets it to mode 8
	TCCR1B |= (1<<CS11); // This sets it to mode 8
	ICR1 = 19999; 
	OCR1A = 1500;
	DDRB |= (1<<DDRB5); //OC1A Set PDS
	
	while (1)
	{
		for(int i=400; i<2000; i++)
		{
			OCR1A = i;
			_delay_ms(10);
		}
		for(int i=2000; i>400; i--)
		{
			OCR1A = i;
			_delay_ms(10);
		}
	}
}*/

//	Author: Danielis Maizelis
//-------------------------------------------------------------------------------------------------------------------------------
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000U
#include <avr/io.h>
#include <avr/interrupt.h> // includes an interrupt
#include <util/delay.h> // includes an interrupt
#include <stdlib.h> 

int random_v();
//-------------------------------------------------------------------------------------------------------------------------------

volatile uint16_t Overflows;
bool reaction_timer_on = 0;
float reaction_time;
int to_make_a_second = 62500;

ISR(INT0_vect) // interrupt vector
{
	reaction_timer_on = 1;
	
	if(TCNT1*to_make_a_second > 1000)
	{
		reaction_time = 2;
	}
	else if(TCNT1*to_make_a_second <= 100)
	{
		reaction_time = 1;
	}
	else
	{
		reaction_time = 1+(TCNT1*to_make_a_second)/1000; 
	}
	
	PORTB |= 0b00000010; // turns on a second led
}
/*
ISR(TIMER0_OVF_vect)
{
	Overflows++;
	if((PIND & 0x01) == 0x01) // If the output is high
	{
		if(Overflows >= (62*reaction_time)) // 1 or 2 ms has elapsed
		{
			PORTD &= ~(1<<PORTD0); // Turn the output low
		}
	}
	if((PIND & 0x01) == 0x00)  // If the output is low
	{
		if(Overflows >= (1249)) // 20 ms has elapsed the whole thing
		{
			PORTD |= (1<<PORTD0); // Turn the output high
			Overflows = 0; // Reset overflows
		}
	}

}*/

int main(void)
{
	int random_value = random_v();// Random value that should have been working commented below
	
	//Timer 0 
	/*TCNT0 = 0;
	TCCR0B |= (1<<CS00); // no pre-scaler
	TIMSK0 |= (1<<TOIE0);
	
	//Timer 1
	TCNT1 |= 0b0000100;*/
	
	// Pins for the LEDs
	DDRB = 0b00000011; // Sets PB0 and PB1 as outputs
	PORTB = 0b00000000;
	
	// Pull-up for a button
	/*PORTD = 0b00000100;
	DDRD = 0b00000000;*/
	
	//interrupt
	/*
	EICRA = 0b00000010; //ISC0n to be sent on falling edge - so when the button is pressed from 1 to 0
	//EICRA = 0b00000010; //ISC0n to be sent on rising edge - so when the button is pressed from 0 to 1
	EIMSK = 0b00000001; // Enables INT0, basically the interrupt, otherwise it won't work*/
	
	sei();
	
	_delay_ms(1000);
	PORTB |= 0b00000001; // turns on a first led
	PORTB |= 0b00000010; // turns on a second led
	
	//TCNT1 = 0; // Starts the counter
	//PORTB = 0b00000000; // turns on a first led
	//PORTB = 0b00000000; // turns on a second led
	
}

int random_v()
{
	return rand() % 3000 + 1000; // Set from 3-4seconds
}

