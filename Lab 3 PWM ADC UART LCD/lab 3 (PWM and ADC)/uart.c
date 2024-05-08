#include "main.h"

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
void USART_Transmit(unsigned char data) // Sending 5 to 8 bits
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}


