#include "../main.h"


void btnSetupIrq(void)
{
	EICRA |= (1<<ISC01);
	EIMSK |= (1<<INT0);
}

void btnPolling(void)
{
	if (!(PIND & (1 << PORTD2)))
	{
		_delay_ms(100);					  // Button debouncing delay
		while (!(PIND & (1 << PORTD2))); // Wait for button release
		PORTB   ^= (1<<PORTB5); // Toggle the pin for
	}
}