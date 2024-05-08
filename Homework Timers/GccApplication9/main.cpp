//	Author: Danielis Maizelis
//-------------------------------------------------------------------------------------------------------------------------------
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000U
#include <avr/io.h>
#include <avr/interrupt.h> // includes an interrupt
#include <util/delay.h> // includes an delay
#include <stdlib.h> 

int random_v();
//-------------------------------------------------------------------------------------------------------------------------------

volatile uint16_t Overflows;
int reaction_timer_on = 0;
float reaction_time;
int max_value = 50000*10000;
int min_value = 600000;
int counter;
int score;
int time_delay;
//bool on = 0;

ISR(INT0_vect) // interrupt vector
{
	if (reaction_timer_on == 1)
	{	
		int counter = TCNT1;
		if(counter >= max_value) // Min score, servo would move a lot
		{
			reaction_time = 1.4;
			PORTB = 0b00000010; // turns on a second led
		}
		else if(counter <= min_value) // Max score, servo would not move
		{
			reaction_time = 0.5;
			PORTB = 0b00000000;
		}
		else // In between max and min scores, would get the appropriate servo movement
		{
			//reaction_time = 0.6+((counter-min_value)/(max_value-min_value));
			reaction_time = 0.8;
			PORTB = 0b00000100;
		 
		}
		score = round((1/reaction_time)*10-5); // a score from 0 to 5*/
		PORTB |= 0b00000010; // turns on a second led
		//_delay_ms(1000);
		reaction_timer_on = 2;
	}
}

ISR(TIMER0_OVF_vect)
{
	Overflows++;
	
	if((PINC & 0x01) == 0x01) // If the output is high
	{
		if(Overflows >= (62*reaction_time)) // 1 or 2 ms has elapsed
		{
			PORTC &= ~(1<<PORTC0); // Turn the output low
		}
	}
	if((PINC & 0x01) == 0x00)  // If the output is low
	{
		if(Overflows >= (1249)) // 20 ms has elapsed the whole thing
		{
			PORTC |= (1<<PORTC0); // Turn the output high
			Overflows = 0; // Reset overflows
		}
	}
}


void Set_servomax()
{
	time_delay = 2;
}

void Set_servomin()
{
	time_delay = 1;
}


int main(void)
{
	int random_value = random_v();// Random value that should have been working commented below
	
	//Timer 0 
	DDRC = 0b11111111;
	TCNT0 = 0;
	TCCR0B |= (1<<CS00); // no pre-scaler
	TIMSK0 |= (1<<TOIE0);
	
	
	//Timer 1
	TCNT1 |= 0b0000100;
	TCCR1B |= (1<<CS02); // Selects a pre-scaler
	
	
	// Pins for the LEDs
	DDRB = 0b00001111; // Sets PB0 and PB1 as outputs
	PORTB = 0b00000000;
	
	// Pull-up for a button
	DDRD = 0b00000000;
	PORTD = 0b00000100;
	
	//interrupt
	EICRA = 0b00000010; //ISC0n to be sent on falling edge - so when the button is pressed from 1 to 0
	//EICRA = 0b00000010; //ISC0n to be sent on rising edge - so when the button is pressed from 0 to 1
	EIMSK = 0b00000001; // Enables INT0, basically the interrupt, otherwise it won't work
	
	//Allows the interrupts
	sei();
	
	while(reaction_timer_on != 2)
	{
		for(int i=0; i<=random_value; i++)
		{
			_delay_ms(1);
		}
		//n = 1;
		PORTB |= 0b00000001; // turns on a first led
		TCNT1 = 0; // Starts the counter
		reaction_timer_on = 1;

	}
}

int random_v()
{
	int hello = rand() % 2000 + 2000; 
	return hello; // Set from 2-4seconds
}

