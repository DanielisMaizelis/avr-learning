#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "buttonpress.h"
#include "ledblink.h"
#define FLASHOFF 0
#define FLASHONFULL 1
#define FLASHONHALF 2
#define FLASHSLOWBLINK 3
#define FLASHFASTBLINK 4

unsigned char FlashLightState = FLASHFASTBLINK;
unsigned char delaycounter = 0;

int main(void)
{
	initButton();
	
    while (1) 
    {
		if(buttonPressed()){
			switch(FlashLightState){
				case FLASHOFF:
					FlashLightState = FLASHONFULL;
					break;
				
				case FLASHONFULL:
				FlashLightState = FLASHONHALF;
				break;
				
				case FLASHONHALF:
				FlashLightState = FLASHSLOWBLINK;
				break;
				
				case FLASHSLOWBLINK:
				FlashLightState = FLASHFASTBLINK;
				break;
				
				case FLASHFASTBLINK:
				FlashLightState = FLASHOFF;
				break;
			}  
		}

	    ////////////////Handling the output based on the state.
		switch(FlashLightState){
			case FLASHOFF:
				led_off();
				break;
				
			case FLASHONFULL:
				led_on();
				break;	
			
			case FLASHONHALF:
				led_toggle();
				break;
				
			case FLASHSLOWBLINK:
				if(delaycounter >= 20){
					led_toggle();
					delaycounter = 0;
				}
				break;
				
			case FLASHFASTBLINK:
				if(delaycounter >= 10){
					led_toggle();
					delaycounter = 0;
				}
				break;
		}

		_delay_ms(5);
		delaycounter++;
	}
}


