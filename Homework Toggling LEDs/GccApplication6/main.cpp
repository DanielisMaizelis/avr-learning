//	Author: Danielis Maizelis
//	???????????????
//------------------------------------------------------------------------------------------------------------------------------
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//-------------------------------------------------------------------------------------------------------------------------------


class Toggle // Class for toggling the LED with the press of a button
{
	private: // Inaccessible variables and/or methods
	int Delay;
	// LEDs get toggled
	int toggle_leds(int random_number, int delay) // Method for toggling LEDs
	{
		int a = 0; // Counter for delay
		bool off = 0; // Indicator that the roulette has stopped
		for(int i=0; i<random_number; i++)
		{
			a++; // Counts up to 8 to slow down the delay every time
			if(i%8 == 0)
			{
				a = 0; // Renews the LED in the roulette
				delay*=1.4; // Slows down the roulette every 8 LED flashes
			}
			PORTA = (1<<a);
			_delay_ms(delay);
			if(i== random_number-1)  // Indicator showing that the state is off
			{
				off = 1;
			}	
		}
		PORTA = (1<<a); // Keeps the last LED on once finished
		return off; // Returns the indicator that the state is off
	}
	
	public: // Accessible variables and/or methods
	Toggle(int delay) //Constructor for the Toggle class
    {
        Delay = delay;
    }
	//Getter
	int get_delay() {return Delay;}
	// Start of the program
	void start()
	{
		int button1; // Button pin
		bool state; // Pin for getting
		bool toggle = 0; // State for starting the toggle
		int random_value = 69; // Random value that should have been working commented below
		//srand(8);
		//int random_value = rand() % 7;
		DDRA =  0b11111111; // Pins for the LEDs 
		PORTA = 0b00000000; // Pins for the LEDs 
		DDRC = 0b00000000; // Pin for the button1
		PINC = 0b00000001; // Pin for the button1
		button1 = PINC & 0b00000001;
		while(1) // This loop works until the button is pressed
		{
			if(button1 == 1)
			{
				button1 = PINC & 0b00000001;
			}
			else
			{
				toggle = 1;
				break;
			}
		}
		if (toggle == 1) // Changes the state to toggling LEDs
		{
			while(state == 0) // Stops the loop if the LEDs no longer run
			{
				state = toggle_leds(random_value, get_delay());	// Sets the delay and the 'random' value to the toggling
			}
		}
		toggle = 0;
	}
};

int main(void) // Main function where the class is called out
{
	int delay = 30; // 30 ms delay set for the program
	Toggle program = Toggle(delay); // program is the object of the toggle class
	program.start(); // Program is started by calling out the start() method
}


