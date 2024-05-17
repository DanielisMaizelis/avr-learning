#include "main.h"
/*void clearScreen()
{
	command(0b00000110);
	command(0b00000001);
	_delay_ms(20);
}


void command(char cmd) // RS = 0 (Command), R/W = 0 (Write), Enable is 1
{
	DATA    = cmd;
	CONTROL |= (1<<EN);
	_delay_ms(1);
	CONTROL &= 0x00;
}

void setData(char data) // RS = 1 R/W = 0, Enable = 1
{
  DATA = data;
  CONTROL |= (1 << RS);  // RS = 1 for data
  CONTROL &= ~(1 << RW); // RW = 0 for write
  CONTROL |= (1 << EN);  // Enable pulse
  _delay_us(1);          // Short delay
  CONTROL &= ~(1 << EN); // Disable pulse
  _delay_ms(2);          // Wait for the data to be written

}


void lcdInit()
{
	DDRD |= 0xFF;
	DDRB |= (1<< RS)|(1<< RW)|(1<< EN);
		
		
	_delay_ms(1000); // Wait for the LCD to power up
		
	// 8-bit mode 2 rows
	command(0b00111000);
		
	// Display on/off
	command(0b00001100);
	clearScreen();
}
*/

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

void setCursor(uint8_t row, uint8_t col) {
	uint8_t address;

	// Calculate the address based on the row and column
	if (row == 0) {
		address = col;
		} else {
		address = 0x40 + col;
	}

	// Send the command to set the DDRAM address
	command(0b10000000 | address);
}
void lcdInit()
{
	DDRD |= 0xFF;
	DDRB |= (1<< RS)|(1<< RW)|(1<< EN);
	
	//clearScreen();
	
	_delay_ms(50); // Wait for the LCD to power up
	
	// 8-bit mode 2 rows
	command(0b00111000);
	
	// Display on/off
	command(0b0001110);
	//setData('0');
	clearScreen();
}
void displayVoltageLcd1(char * word)
{
	while (*word)
	setData(*word++);
}