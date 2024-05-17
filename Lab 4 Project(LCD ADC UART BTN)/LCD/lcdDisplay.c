#include "include/main.h"

void displayPage(uint8_t*headLine, uint8_t*value, uint8_t*type)
{
	lcd_puts(headLine);
	lcd_puts((uint8_t*)": ");
	lcd_puts(value);
	lcd_puts((uint8_t*)" ");
	lcd_puts(type);
}



