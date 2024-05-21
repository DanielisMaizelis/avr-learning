#ifndef MAIN_H_
#define MAIN_H_

//****************************************************************************
//Defines

// Clock settings
#define F_CPU		16000000UL
#define BAUD		9600
#define MYUBRR		F_CPU/16/BAUD-1   // Calculated Baud rate register

// Redefined Interrupt service routine names
#define DEBOUNCE_TIMER0_OVF_vect TIMER0_OVF_vect
#define BUTTON_INT0_vect		 INT0_vect

// Types of display of data
#define DISPLAY_LCD	 0
#define DISPLAY_UART 1

// LCD pages
#define LCD_PAGE_1 0
#define LCD_PAGE_2 1
#define LCD_PAGE_3 2
#define LCD_PAGE_LIMIT 3

// Button press states
#define BUTTON_NOT_PRESSED 0
#define BUTTON_PRESSED	   1
#define BUTTON_DEBOUNCE_ON	   2

// Button debounce
#define DEBOUNCE_LIMIT 200

// Channel register values:
#define CH0_REGISTER (1 << REFS0)
#define CH1_REGISTER (1 << REFS0)|(1 << MUX0)
#define CH2_REGISTER (1 << REFS0)|(1 << MUX1)
//****************************************************************************
// Includes
#include "lcd.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
//****************************************************************************


//****************************************************************************
// Function Definitions
void setupTim0Irq(void);
void displayPage(uint8_t*, uint8_t*, uint8_t*);
void btnSetupIrq(void);
void setCursor(uint8_t, uint8_t);
void clearScreen();
void adcInit();
void displayVoltageLcd1(char*);
void command(char); // RS = 0 (Command), R/W = 0 (Write), Enable is 1
void setData(char);
void USART_Init(unsigned int);
void USART_Transmit(unsigned char); // Sending 5 to 8 bits
void usartTransmitString(char *);
//****************************************************************************
#endif /* MAIN_H_ */