// Setup / includes:
#define  F_CPU 16000000U
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//---------------------------------------------------------------------------------

// Global Variables:
#define TIM0_1SECOND		   61
#define RIGHT_LED			   5
uint8_t  counterTimer0 = 0;
uint8_t	 tim0Flag	   = 0;


#define TIM1_1SECOND		   30
#define LEFT_LED			   4
uint8_t  counterTimer1 = 0;
uint8_t	 tim1Flag	   = 0;
//---------------------------------------------------------------------------------


// Interrupts:
ISR(TIMER0_OVF_vect)
{
	counterTimer0++;

	if(counterTimer0 >= TIM0_1SECOND && tim0Flag)
	{
		counterTimer0 = 0;
		tim0Flag = 0;
	}
	if(counterTimer0 >= TIM0_1SECOND && !tim0Flag)
	{
		counterTimer0 = 0;
		tim0Flag = 1;
	}
}

ISR(TIMER1_OVF_vect)
{
	counterTimer1++;

	if(counterTimer1 >= TIM1_1SECOND && tim1Flag)
	{
		counterTimer1 = 0;
		tim1Flag = 0;
	}
	if(counterTimer1 >= TIM1_1SECOND && !tim1Flag)
	{
		counterTimer1 = 0;
		tim1Flag = 1;
	}
}
//---------------------------------------------------------------------------------



int main(void)
{
	//turnLEDsStep1();
	//blinkLED();
	
	DDRB  |= 0b00110000;
	
	// To set a timer 0, I need to turn on a pre-scaler to CS00 and CS02 to 1024	
	TCNT0	= 0;					 // Begins the counter from 0
	TCCR0B |= (1<<CS02)|(1<<CS00);   // Sets the pre-scaler
	TIMSK0 |= (1<<TOIE0);			 // Enables overflow
	
	// To set a timer 1, I need to turn on a pre-scaler to 8
	TCNT1	= 0;
	TCCR1B |= (1<<CS11);
	TIMSK1 |= (1<<TOIE1);
	
	// Button
	// Set up an external interrupt
	
	// Set it up to a pull up
	
	
	// Make it a rising edge
	
	

	sei();							// Enables all interrupt settings
	
	
    while (1) 
    {
		if(tim0Flag)
		{
			PORTB |= (1<<RIGHT_LED);
		}
		else
		{
			PORTB &= 0x00;
		}
		if(tim1Flag)
		{
			PORTB |= (1<<LEFT_LED);
		}
		else
		{
			PORTB &= 0x00;
		}
    }
}



void turnLEDsStep1()
{
	DDRB  |= 0b00110000;
	PORTB |= 0b00110000;
}

void blinkLED()
{
	DDRB  |= 0b00110000;
	PORTB |= 0b00000000;
	
	while(1)
	{
		_delay_ms(1000);
		PORTB |= (1<<5);
		_delay_ms(1000);
		PORTB &= 0x00;				
	}
}