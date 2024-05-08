#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR		F_CPU/16/BAUD-1   // Calculated Baud rate register - we get bits that look like 0b000010010

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

volatile uint16_t result;
uint8_t flag = 0;

ISR(ADC_vect)
{
	result = ADC;
	flag   = 1;
}

void fastPwmTim1()
{
	 DDRB |= (1 << DDB1);
	 // Configure Timer 1 for Fast PWM mode with ICR1 as TOP
	 TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Clear OC1A on compare match, set OC1A at BOTTOM
	 TCCR1B |= (1 << WGM13) | (1 << WGM12);  // Fast PWM mode with ICR1 as TOP
	 TCCR1B |= (1 << CS11)|(1 << CS10);		 // Set prescaler to 8

	 // Set ICR1 to define the PWM period
	 ICR1 = 1000; 

	 // Optionally, set OCR1A to define the initial PWM duty cycle
	 OCR1A = 100; 
}

void phCorrPwmTim1()
{
	DDRB |= (1 << PORTB1);
	// Set Phase Correct PWM mode with non-inverting output on OC1A (Pin PB1)
	TCCR1A |=  (1 << COM1A1) | (1 << WGM11);
	// Set WGM13, CS10, and CS12 bits for Phase Correct PWM mode with prescaler 64
	TCCR1B |= (1 << WGM13) | (1 << CS10) | (1 << CS11);
	
	// Set ICR1 to define the PWM period
	ICR1 = 1000; 

	// Optionally, set OCR1A to define the initial PWM duty cycle
	OCR1A = 900; 
}


void fastPwmTim0()
{
	DDRD   |= (1<<PORTD6);
	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM mode, non-inverting
	TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler = 64
 
	// Set the initial duty cycle (0 to 255)
	OCR0A = 127; // 50% duty cycle
}


void adcSetup()
{
	 DDRC   |= 0x00;					  // Set the pins for analog as input
	 PORTC  |= 0x00;			          // Set the pins for analog as input
	 ADCSRA |= (1 << ADEN) | (1 << ADIE)| (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, ADC Interrupt
	 ADMUX  |= 1 << REFS0;				  // Set reference voltage to AVCC
	// ADMUX  |= 1 << ADLAR;				  // Left adjust result 


	 // Set ADC channel to 0
	 //ADMUX &= ~(1 << MUX0) & ~(1 << MUX1) & ~(1 << MUX2) & ~(1 << MUX3);
	 ADMUX |= (1 << MUX0);

	 // Start conversion and interrupts
	 ADCSRA |= (1 << ADSC)|(1<< ADIE);
}

void USART_Transmit(unsigned char data) // Sending 5 to 8 bits
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8); // High bit?
	UBRR0L = (unsigned char) ubrr;	   // Low bit?
	
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00)|(0<<UMSEL00);
	//UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	//UCSR0C = (1<<UCSZ00)|(1<<UCSZ01)(0<<UMSEL00);
}
	
	
void usartTransmitString(char *str)
{
	while(*str)
		USART_Transmit(*str++);
	USART_Transmit('\n');
}


void float_to_string(float value, char* buffer, int precision) {
	int int_part = (int)value;
	float remainder = value - int_part;
	int index = 0;

	// Convert the integer part to string
	while (int_part != 0) {
		buffer[index++] = int_part % 10 + '0';
		int_part /= 10;
	}

	// Reverse the integer part in the buffer
	for (int i = 0; i < index / 2; i++) {
		char temp = buffer[i];
		buffer[i] = buffer[index - i - 1];
		buffer[index - i - 1] = temp;
	}

	// Append the decimal point
	buffer[index++] = '.';

	// Convert the fractional part to string
	for (int i = 0; i < precision; i++) {
		remainder *= 10;
		int digit = (int)remainder;
		buffer[index++] = digit + '0';
		remainder -= digit;
	}

	// Null-terminate the string
	buffer[index] = '\0';
}

int main(void)
{
	char msg[10];
	// Set PB1 (OC1A) as output for PWM
	// Initialize PWM in Fast PWM mode
	//fastPwmTim1();
	DDRB |= (1<<PORTB3);
	// Or Initialize PWM in Phase Correct PWM mode
	adcSetup();
	USART_Init(MYUBRR);
	phCorrPwmTim1();
	fastPwmTim0();
	sei();

	float resultf;
	while (1)
	{
		ADCSRA |= (1 << ADSC)|(1<< ADIE);
		if(flag)
			PORTB |= (1<<PORTB3);
			
		float_to_string((result*5.0)/1024.0, msg, 3);
		strcat(msg," V");
		usartTransmitString(msg);
		_delay_ms(200);
		ADCSRA &= ~((1 << ADSC)|(1<< ADIE));
	 
	}

	return 0;
}
