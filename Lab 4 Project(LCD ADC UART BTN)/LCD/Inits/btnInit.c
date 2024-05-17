#include "../include/main.h"


void btnSetupIrq(void)
{
	EICRA |= (1<<ISC01); // Activate falling edge
	EIMSK |= (1<<INT0);  // Activate int0
}