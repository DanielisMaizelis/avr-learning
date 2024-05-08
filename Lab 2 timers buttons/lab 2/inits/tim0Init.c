#include "../main.h"


void setupTim0Irq(void)
{
	TCCR0B |= (1 << CS01)|(1<<CS00);
	TIMSK0 |= (1<<TOIE0);
}