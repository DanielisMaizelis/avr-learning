/*
 * GccApplication2.c
 *
 * Created: 08/09/2022 10:23:50
 * Author : Danielis Maizelis
 */ 

//------------------------------------------------------------------------------------------------------------
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------------------------------


int toggle_leds(int random_number, int delay);
//int end_of_toggling(int delay, int pin);
//int random_number(int min_num, int max_num);


int main(void)
{
	DDRA =  0b11111111;
	PORTA = 0b00000000;
	DDRC = 0b00000000;
	PORTC = 0b00000001;

	int button1;
	int pin;
	int random_value = 0;//rand() % 7;
	random_value += 60;
	
	/*
		button1 = PINC & 0b00000001;`
	if(button1 == 1)
		{
			PORTA = (1<<i);
			_delay_ms(delay);
			button1 = PINC & 0b00000001;
		}*/
	while(pin == 0)
	{
		pin = toggle_leds(random_value, 200);	
	}
}

int toggle_leds(int random_number, int delay)
{
	int a = 0;
	int off = 0;
	for(int i=0; i<random_number; i++)
	{
		a++;
		if(i%8 == 0)
		{
			a = 0;
			delay*=1.4;
		}
		PORTA = (1<<a);
		_delay_ms(delay);
		if(i== random_number-1)
		{
			off = 1;
		}	
	}
	PORTA = (1<<a);
	return off;
}