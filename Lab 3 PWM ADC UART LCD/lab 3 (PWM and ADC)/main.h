 #ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR		F_CPU/16/BAUD-1   // Calculated Baud rate register - we get bits that look like 0b000010010
#define DATA    PORTD
#define CONTROL PORTB

#define RS		PORTB3
#define RW		PORTB4
#define EN		PORTB5

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>



void USART_Transmit(unsigned char); // Sending 5 to 8 bits
void adcSetup();
void displayVoltageLcd(char*);
void clearScreen();
void lcdInit();
void usartTransmitString(char*);
void USART_Init(unsigned int);


#endif /* MAIN_H_ */