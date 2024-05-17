#include "main.h"

void command(char cmd) // RS = 0 (Command), R/W = 0 (Write), Enable is 1
{
	DATA    = cmd;
	CONTROL |= (1<<EN);
	_delay_ms(1);
	CONTROL &= 0x00;
}

void setData(char data) // RS = 1 R/W = 0, Enable = 1
{
	DATA    = data;
	CONTROL |= (1<<RS)|(1<<EN);
	_delay_ms(1);
	CONTROL &= ~(1<<EN); // Rs stay, enable 0

}
void clearScreen()
{
	command(0b00000110);
	command(0b00000001);
	_delay_ms(20);
}

void lcdInit()
{
	DDRD |= 0xFF;
	DDRB |= (1<< RS)|(1<< RW)|(1<< EN);
	
	//clearScreen();
	
	_delay_ms(50); // Wait for the LCD to power up
	
	// 8-bit mode 2 rows
	command(0b00110000);
	
	// Display on/off
	command(0b00001100);
	//setData('0');
	clearScreen();
}





void displayVoltageLcd(char * word)
{
	while (*word)
	setData(*word++);
}