#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


#include "button.h"
#include "led.h"
#define FLASHOFF 0
#define FLASHONFULL 1
#define FLASHONHALF 2
#define FLASHSLOWBLINK 3
#define FLASHFASTBLINK 4

unsigned char delaycounter = 0;
unsigned char FlashLightState = FLASHFASTBLINK;


int main(void)
{
    while (1) 
    {
	  if(buttonPressed())
	  {
		  switch(FlashLightState)
		  {
			case FLASHOFF:
				FlashLightState = FLASHONFULL;
				break;
			case FLASHONFULL:
				FlashLightState = FLASHONFULL;
				break;
			case FLASHOFF:
				FlashLightState = FLASHONFULL;
				break;
			case FLASHOFF:
				FlashLightState = FLASHONFULL;
				break;
			case FLASHOFF:
				FlashLightState = FLASHONFULL;
				break;
		  }
		  switch(FlashLightState)
		  {
			case FLASHOFF:
				led_Off();
				break;
			case FLASHONFULL:
				led_On();
				break;
			case FLASHONHALF:
				led_Toggle();
				break;
			case FLASHSLOWBLINK:
				FlashLightState = FLASHONFULL;
				break;
			case FLASHFASTBLINK:
				if(delaycounter >= 10)
				{
					led_Toggle();
					delaycounter=0;
				}
				FlashLightState = FLASHONFULL;
				break;
		   }
	  }
	  
	}
}
