/*
 * GccApplication3.c
 *
 * Created: 20/09/2022 08:56:52
 * Author : Maizel
 */ 

#define F_CPU 16000000
#include "util/delay.h"
#include <avr/io.h>

 
void  timer0_init()
{
	TCCR1B |= (1 << CS02);
	TCNT1 = 0;
}
 
int main(void)
{
	DDRA |= (1 << 0);
	timer0_init();
	while (1)
	{
		if(TCNT1 >= 1249)
		{
			PORTA ^= (1 << 0);   
			TCNT1 = 0;           
		}
	}
}

