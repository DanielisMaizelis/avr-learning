#include "main.h"

// Global variables
uint8_t gBtnFlag = 0;		 // btn flags for debounce
uint8_t gOverflowTim0 = 0;   // Overflow counter for timer 0

ISR(INT0_vect) // Button Interrupt
{
	if(gBtnFlag == 0)
	{
		gBtnFlag = 1;
	}
	if(gBtnFlag == 1) // Button is pressed
	{
		TCNT0    = 0;			// Start counting the tim0 counter
		PORTB   ^= (1<<PORTB5); // Toggle the pin for LED
		gBtnFlag = 2;			// Set a different state for debounce
	}
	
}

ISR(TIMER0_OVF_vect) // Debounce Timer 0 Interrupt
{
	gOverflowTim0++;
	if(gBtnFlag == 2 && gOverflowTim0 >= 200) // Counter is reached and button was pressed
	{
		
		gBtnFlag     = 0;		//
		gOverflowTim0 = 0;
	}
}

ISR(TIMER1_COMPA_vect) // Blink Timer 1 Interrupt, whithout ctc pin
{
	PORTB ^= (1<<PORTB0);
}


static void clearLeds(void)
{
	PORTD &= ~((1<<RED_LED)|(1<<GREEN_LED)|(1<<YELLOW_LED));			
}

int main(void)
{
	lightStates_t ls = STOP;
	cli();				// Disables all interrupts
	pinSetup();			// GPIO pin setup - leds and buttons
	setupTim1Irq();		// Timer 1 setup blink led using CTC
	setupTim0Irq();			// Timer 0 for button debounce
	btnSetupIrq();
	sei();				// Enables all interrupts

    while (1) 
    {
		//btnPolling();
		switch(ls)
		{
			case STOP:
				clearLeds();
				PORTD |= (1<<RED_LED);
				_delay_ms(4000);
				ls = PREPARE;
				break;	
			case PREPARE:
				clearLeds();
				PORTD |= (1<<RED_LED)|(1<<YELLOW_LED);
				_delay_ms(2000);
				ls = GO;
				break;
			case GO:
				clearLeds();
				PORTD |= (1<<GREEN_LED);
				_delay_ms(6000);
				ls = STOP_IF_NOT_SAFE;
				break;
			case STOP_IF_NOT_SAFE:
				clearLeds();
				PORTD |= (1<<YELLOW_LED);
				_delay_ms(2000);
				ls = STOP;
				break;
		}
    }
	return 0;
}

