//Author: Danielis Maizelis
//------------------------------------------------------------------------------------------------------------------------------
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------------------------------------------------


void  timer0_init()
{
	TCCR1B |= (1 << CS02);
	TCNT1 = 0; // timer 1
}

// We need to select the right bot in TCCR0 Register

int main(void)
{
	DDRA |= (1 << 0); 
	timer0_init();
	while (1)
	{
		if(TCNT1 >= 1249)
		{
			PORTA = (1 << 0);
			TCNT1 = 0;
		}
	}
}/*
int main(void)
{
	int timer = 0;
	int elapsed_time;
    while (1) 
    {/*
		if(button is pressed)
		{
			elapsed_time = timer;
			timer = 0;
		}
		else
		{
			timer++;
		}*/
    }
}

*/