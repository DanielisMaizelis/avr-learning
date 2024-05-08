#define F_CPU 16000000U
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
			
#define BAUD		9600		     // Baud rate
#define MYUBRR		F_CPU/16/BAUD-1   // Calculated Baud rate register - we get bits that look like 0b000010010

#define TIM0_1SECOND		   61
#define LED_10				   2
#define LED_8				   0


uint8_t  counterTimer0 = 0;
uint8_t	 tim0Flag	   = 0;

uint8_t flag= 0;
unsigned char buff;

void USART_Transmit(unsigned char data) // Sending 5 to 8 bits
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

	
unsigned char USART_Receive(void)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

ISR(USART_RX_vect)
{   
	//PORTB  |= (1<<5);
	buff = USART_Receive();
	if(buff == '1')
		flag = 1;
	
	else if(buff == '0')
		flag = 0;
}
/*
ISR(TIMER0_OVF_vect) 
{ 
	counterTimer0++;
	if(counterTimer0 >= TIM0_1SECOND && tim0Flag)
	{
		counterTimer0 = 0;
		tim0Flag = 0;
		TCNT0   = 0;
		USART_Transmit('1');
		
	}
	if(counterTimer0 >= TIM0_1SECOND && !tim0Flag)
	{
		counterTimer0 = 0;
		tim0Flag = 1;
		TCNT0   = 0;	
		USART_Transmit('0');
	}
}*/




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





int main(void)
{
	DDRB   |= 0b11111111;
	USART_Init(MYUBRR);
	
	/*
	// Timer0 no pre-scaler
	TCNT0   = 0;
	TCCR0B |= (1<<CS02)|(1<<CS00);   // Sets the pre-scaler
	TIMSK0 |= (1<<TOIE0);			 // Enables overflow
	*/
	sei();

			
	//USART_Transmit('A');
	while(1)
	{
		 if(flag)
			PORTB  |= (1<<5);
		 else
			PORTB  &= 0x00;
		
		/*
		if(tim0Flag)
			PORTB  |= (1<<2);
		
		else
			PORTB &= ~(1<<2);
			*/
		
		
		
		 /* Get and return received data from buffer */
		  
		  
		
		//else if(USART_Receive() == '0')
			//PORTB  &= 0b00000000; // Turn off
		
		/*
		if(tim0Flag)
		{
			PORTB  &= 0x00; 
			PORTB  |= (1<<LED_10);
		}
		else
		{
			PORTB  &= 0x00;
			PORTB  |=  (1<<LED_8);
			//USART_Transmit('b');
		}*/
	}
	return 0;
}

