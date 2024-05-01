//-------------------------------------------------------------------------------------------------------------------------------------------
#define F_CPU 16000000
#define TXHI PORTD |= 0B00000010
#define TXLO ; PORTD &= ~0B00000010 //

#include <avr/io.h>
#include <util/delay.h>
//-------------------------------------------------------------------------------------------------------------------------------------------


int main(void) // Not supposed to take anything
{
	DDRD |= 0B0000010;
    while (1)														
    {
		//led_blink(4000000);
		TXLO;
		_delay_us(2000000); // time in nanoseconds
		TXHI;
		_delay_us(2000000);
	}
}


//void led_blink(unsigned int hello)
//{
//	TXLO;
	//_delay_us(hello); // time in nanoseconds
	//TXHI;
	//_delay_us(hello);
//}


	