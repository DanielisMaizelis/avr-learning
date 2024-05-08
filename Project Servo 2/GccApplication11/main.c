//------------------------------------------------------------------------------------------------------------
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#define __DELAY_BACKWARD_COMATIBILE_



/*
int random_create();
void set_timer();
void checkIfHighscore(float score);
void eeprom_w(int address, float result);
void Set_servomax();
void Set_servomin(float angle);*/
//------------------------------------------------------------------------------------------------------------

uint16_t overflow_t0 = 0;
uint16_t overflow_t2 = 0;
float highscore = 1.05;
float timeDelay = 1;

ISR(TIMER2_OVF_vect)
{
	overflow_t2++;
}

ISR(TIMER0_OVF_vect)
{
	overflow_t0++;
	if ((PINB & 0x01) == 0x01)
	{ //If output is high
		if (overflow_t0 >= (31*timeDelay))
		{
			PORTC &= ~(1<<PORTC0); // Turn the output low
		}
	}
	if ((PINB & 0x01) == 0x00)
	{ //If output is low
		if (overflow_t0 >= 1249)
		{ //If 20 ms have elapsed
			PORTC |= (1<<0); //Make output high (set the pin HIGH)
			overflow_t0 = 0; //End of the cycle
		}
	}
}
void set_timer()
{
	overflow_t2 = 0;
	TCNT2 = 0;
}

int random_create()
{
	int number = rand() % 2000 + 2000;
	return number; // Set from 2-4seconds
}

void eeprom_w(int address, float result)
{
	eeprom_write_float (( float *) address, result);
}

void checkIfHighscore(float score)
{
	if(score < highscore)
	{
		highscore = score;
		
		//highscore
	}
	else
	{
		//low-score
	}
}

void Set_servomax()
{
	timeDelay = 2;
}

void Set_servomin(float angle)
{
	if(angle < 0.3){
		timeDelay = 0.3;
	}
	if(angle >= 0.3 && angle < 0.6){
		timeDelay = 0.8;
	}
	if(angle >= 0.6){
		timeDelay = 1.5;
	}
}

int main(void)
{
	float score = 0;
	int address = 0;
	int random_value = random_create();
	
	// Setup for LEDs
	DDRB = 0b00000111;
	PORTB = 0b00000000;
	
	// Pull-up for a button
	DDRD = 0b00000000;
	PORTD = 0b00000100;
	
	//Servo
	DDRC = 0b11111111;
	
	//Timer 0
	TCCR0B |= (1<<CS00);
	TIMSK0 |= (1<<TOIE0);
	
	//Timer 2
	TCCR2B |= (1<<CS22)|(1<<CS21); //Overflow for timer 2 set at 256 pre-scale
	TIMSK2 |= (1<<TOIE2); /* Timer/Counter2 Overflow interrupt enabled */
	
	sei(); /* Global Interrupt Enable */
	
	while(1)
	{

		set_timer();
		for(int i=0; i<=random_value; i++)
		{
			_delay_ms(1);
		}
		
		PORTB |= (1<<0);
		set_timer();
		while (PIND != 0)
		{
		}
		PORTB |= (1<<1);
		score = (overflow_t2*0.004)+TCNT2*0.000016;
		_delay_ms(2000);
		set_timer();
		checkIfHighscore(score);
		eeprom_w(address, score);
		address++;
		PORTB = 0b00000000;
		set_timer();
		TCNT0 = 0;
		Set_servomax();
		_delay_ms(1000);
		Set_servomin(score);
		_delay_ms(5000);
		Set_servomax();
		_delay_ms(3000);
	}
	
}

