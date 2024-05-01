//#include "main.h"
#define F_CPU 16 000 000
#include <avr/io.h>
#include <avr/interrupt.h>

double dutyCycle	  = 10;

uint8_t counterTimer0 = 0;
uint8_t counterTimer1 = 0;
uint8_t tim0Flag	  = 0;
void fastPwmSetup(void);
void tim0Setup(void);
void gpioSetup(void);

ISR(TIMER0_OVF_vect) 
{ 
			
	counterTimer0++;
	if(counterTimer0 >= 60 && tim0Flag)
	{
		counterTimer0 = 0;
		tim0Flag = 0;
		TCNT0   = 0;
	
	}
	if(counterTimer0 >= 60 && !tim0Flag)
	{
		counterTimer0 = 0;
		tim0Flag = 1;
		TCNT0   = 0;	
	}
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 1<<2;
	//TCNT1 = 0;
}
void gpioSetup()
{
	DDRB = (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2);
}

void fastPwmSetup(void)
{
	// 2. Prescaler
	/*
	TCCR1A = (1<<COM1A1)|(1<<WGM13)|(1<<WGM12)|(1<<WGM11)|(1<<WGM10);
	TCCR1B = (1<<CS10);

	// 3. Set up Output compare
	TIMSK1 = (1<<TOIE1);
	OCR1A  = (dutyCycle/100)*255;
	
	//OCR1A  = 10;
	
	// 1. counter to 0
	TCNT1   = 0;*/
	
	TCCR1A |= WGM12;
	TCCR1B = (1<<CS10)|(1<<CS12); //1024

	// 3. Set up Output compare
	TIMSK1 |= (1<<OCIE1A);
	//OCR1A   = 15000;
	//OCR1A = (F_CPU / 1024) * 0.5 - 1;
	OCR1A = 5;
		
	// 1. counter to 0
	TCNT1   = 0;
}

void tim0Setup(void)
{
	TCNT0   = 0;
	TCCR0B |= (1<<CS02)|(1<<CS00);   // Sets the pre-scaler
	TIMSK0 |= (1<<TOIE0);			 // Enables overflow
}

/*
void tim2Setup(void)
{
	TCNT2   = 0;
	TCCR2A |= (1<<WGM22);   // Sets the pre-scaler
	TCCR2B |= (1<<CS00);    // Sets the pre-scaler
	TIMSK0 |= (1<<OCIE2A);  // Enables overflow
	OCR2A   = 99;
}*/

int main(void)
{
	gpioSetup();
	fastPwmSetup();
	//tim2Setup();
	// 2. Prescaler
		
	// 1. counter to 0
	//tim0Setup();
	sei();
				
			
    while (1) 
    {
		if(tim0Flag)
			PORTB |= 1<<1;
		else
			PORTB &= ~(1<<1);
    }
}


