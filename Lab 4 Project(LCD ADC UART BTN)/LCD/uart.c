#include "include/main.h"

void USART_Transmit(unsigned char data) // Sending 5 to 8 bits
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void usartTransmitString(char *str)
{
	while(*str)
	USART_Transmit(*str++);
}
