//--------------------------------------------------------------------------------------------------------------------------------
// Author:	??? ??? ???? ? ?? ?? ? ?? ?? ??? ??? ? ?? ?? ?? ? ??
//			??? ??? ???? ? ?? ?? ? ?? ?? ?V? ??? ? ?? ?? ?? ? ??
//			??? ??? ???? ? ?? ?? ? ?? ?? ??? ??? ? ?? ?? ?? ? ??
//--------------------------------------------------------------------------------------------------------------------------------
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#define __DELAY_BACKWARD_COMATIBILE_
//--------------------------------------------------------------------------------------------------------------------------------

float highscore = 1.05;
float servo_movement = 1;
uint16_t overflow_t0 = 0;
uint16_t overflow_t2 = 0;

ISR(TIMER0_OVF_vect) // Servo overflow for timer0
{
	overflow_t0++;
	if ((PINB & 0x01) == 0x01){ //If output is high
		if (overflow_t0 >= (31 *servo_movement)){
			PORTB &= ~(1<<0); //Set the pin LOW
		}
	}
	if ((PINB & 0x01) == 0x00){ //If output is low
		if (overflow_t0 >= 1249){ //If 20 ms have elapsed
			PORTB |= (1<<0); //Make output high (set the pin HIGH)
			overflow_t0 = 0; //End of the cycle
		}
	}
}

ISR(TIMER2_OVF_vect) // Counts up for the reaction
{
	overflow_t2++;
}

class Servo_assignment
{
	public:	
		void run()
		{
			float score = 0; // Score for the reaction time
			int id = 0; //id for the EEPROM storing 
			int randomNumber = random_number(); // random delay number
			
			// Timer0 no pre-scaler
			TCCR0B |= (1<<CS00);
			TIMSK0 |= (1<<TOIE0);
			
			// LEDs
			DDRD |= 0b00000111; 
			PORTD = 0b00000000; 
			
			// Pull-up for a button
			DDRA |= 0b00000000; 
			PORTA = 0b00000010; 
	
			//Servo
			DDRB = 0b11111111; 
			
			// Timer2 
			TCCR2B |= (1<<CS22)|(1<<CS21); //The pre-scaler is set to 256
			TIMSK2 |= (1<<TOIE2); // Timer2 Overflow interrupt 
	
			sei(); // turns on the interrupts
			
			while(1)
			{
				intro(); // Intro of flashing LEDs to shaw that the game has started
				// LEDs are turned one by another before the final reaction LED flashes
				PORTD = 0b00000100; // First led turns on
				_delay_ms(1000);
				PORTD = 0b00000010;  // Second led turns on
				reset_timer();
				for(int i=0; i<randomNumber; i++) // Loop for setting the random delay
				{
					_delay_ms(1);
				}
				PORTD =  0b00000001; // Final led turns on
				reset_timer();
				while (PINA != 0x00){} // Waits for the button press
				PORTD |= (1<<1); // Sets the other LED for comparison
				score = (overflow_t2*0.004)+TCNT2*0.000016;  //Counts the score
				_delay_ms(2000);
				reset_timer();
				check_high_score(score);
				EEPROM(id, score);
				id++;
				PORTD = 0b00000000;
				reset_timer();
				TCNT0 = 0;
				move_the_servo(score);	
			}
		}
	
	private:
		void intro() // Intro for the 
		{
			for(int i=0; i<15; i++)
			{
				for(int j=0; j<3; j++)
				{
					PORTD = (1<<j);
					_delay_ms(40);
				}
			}
		}	
		void check_high_score(float score)
		{
			if(score < highscore)
			{
				highscore = score; // sets the high (or low) score
				for(int i=0; i<5; i++)
				{
					_delay_ms(500);
					PORTD = 0b00000100;
					_delay_ms(500);
					PORTD = 0b00000000;
				}
			}
			else{
				for (int i=0; i<5; i++) // In case it is not a high score
				{
					_delay_ms(500);
					PORTD = 0b00000001;
					_delay_ms(500);
					PORTD = 0b00000000;
				}
			}
		}
		void move_the_servo(float score)
		{
			set_servomax();
			_delay_ms(1000);
			set_servomin(score);
			_delay_ms(4000);
			set_servomax();
			_delay_ms(3000);
		}

		void EEPROM(int id, float result) // Stores the values into eeprom for high score
		{
			eeprom_write_float (( float *) id, result);
		}

		void reset_timer()
		{
			TCNT2 = 0;
			overflow_t2 = 0;
		}

		int random_number()
		{
			int randomise;
			srand(9);
			randomise = 3000 + rand()%4000; // Sets between 3 and 4 seconds 
			return randomise;
		}

		void set_servomax()
		{
			servo_movement = 2;
		}

		void set_servomin(float score)
		{
			if(score < 0.3)
			{
				servo_movement = 0.3;
			}
			else if(score >= 0.3 && score < 0.6)
			{
				servo_movement = 0.8;	
			}
			else if(score >= 0.6)
			{
				servo_movement = 1.5;
			}
		}
};


int main(void)
{
	Servo_assignment sa;
	sa.run();
}