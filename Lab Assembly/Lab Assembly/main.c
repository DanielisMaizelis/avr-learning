#include <avr/io.h>


int main(void)
{
	volatile int x = 4;
	volatile int y = 3;
	
	volatile int z = y + x;
	
	z = 0;
	
    while (1) 
    {
    }
	
}


