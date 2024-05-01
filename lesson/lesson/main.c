#define  F_CPU 16000000
// Oscilator
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


ISR(TIMER1_COMPA_vect) // Interrupt is triggered when it reaches  the bounadry
{
	PORTB ^= (1<<PORTB5);		
}



int main(void)
{
	// Tells which pin to set up
	
	// 00000000
	// 00100000
	// 00100000
	
	
	// 1. DDRn
	// 2. PORTn
	// 3. Bit shifting to the left
	// 4. OR equals
	
	//DDRB  |= (1<<5);
	DDRB  |= (1<<PORTB5);
	
	//16 000 000/ 1024 == 15 625 -> 1s
	//16 000 000/ 256 ==  62 500 -> 1s
	// counter = 0
	//64 535
	
	TCCR1B |= (1<<CS12)|(1<<CS10)|(1<<WGM12);
	TIMSK1 |= (1<<OCIE1A);
	OCR1A   = 15625*2-1;
	
	
	//ctc -> a 
	//int counter = 0;
	TCNT1 = 0;
	sei();
    while (1) 
    {
	
		/*
		if(TCNT1 == 15625*2-1)
		{
			PORTB ^= (1<<PORTB5);
			TCNT1 =0 ;
		}*/
		//turn on
		//_delay_ms(1000);
		//turn off
		//delay(1sec)
    }
}

