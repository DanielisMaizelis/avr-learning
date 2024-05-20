#include "include/main.h"


// Global Variables
// Make a struct:
volatile uint16_t gAdcValueCh[3];
const    uint8_t  gAdcCh[3]	  = {CH0_REGISTER,CH1_REGISTER,CH2_REGISTER};

uint8_t gAdcChCounter = 0;
uint8_t gBtnFlag	  = BUTTON_NOT_PRESSED;	 // btn flags for debounce
uint8_t gOverflowTim0 = 0;					 // Overflow gAdcChCounter for timer 0
uint8_t gPageCountLcd = LCD_PAGE_1;			 // Page gAdcChCounter for a


ISR(BUTTON_INT0_vect) // Button Interrupt
{
	if(gBtnFlag == BUTTON_NOT_PRESSED)
	{
		gBtnFlag = BUTTON_PRESSED;
	}
	if(gBtnFlag == BUTTON_PRESSED) // Button is pressed
	{
		TCNT0    = 0;					// Start counting the tim0 gAdcChCounter
		gBtnFlag = BUTTON_DEBOUNCE_ON;  // Set a different state for debounce
	}
}

ISR(DEBOUNCE_TIMER0_OVF_vect) // Debounce Timer 0 Interrupt
{
	gOverflowTim0++;
	if(gBtnFlag == BUTTON_DEBOUNCE_ON && gOverflowTim0 >= DEBOUNCE_LIMIT) // gAdcChCounter is reached and button was pressed
	{
		gPageCountLcd++;
		gBtnFlag	  = BUTTON_NOT_PRESSED;		//
		gOverflowTim0 = 0;
	}
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

void displayAllData(uint8_t pageLcd, uint8_t bType)
{
	char voltagePotenStr[20];
	char brightnessStr[10];
	char humidityStr[10];
	float_to_string((gAdcValueCh[0]*5.0)/1024.0, voltagePotenStr, 3);
	float_to_string((gAdcValueCh[1])/1024.0*100, brightnessStr, 1);
	float_to_string((gAdcValueCh[2])/1024.0*100, humidityStr, 1);
	

	if(bType == DISPLAY_LCD)
	{
		lcd_putcmd(LCD_SET_CURSOR|FIRST_ROW);
		switch(pageLcd)
		{
			case LCD_PAGE_1:
			displayPage((uint8_t*)"Voltage",(uint8_t*)voltagePotenStr,(uint8_t*)"V");
			break;
			case LCD_PAGE_2:
			displayPage((uint8_t*)"Light",(uint8_t*)brightnessStr,(uint8_t*)"%");
			break;
			case LCD_PAGE_3:
			displayPage((uint8_t*)"Humidity",(uint8_t*)humidityStr,(uint8_t*)"%");
			break;
		}
		lcd_putcmd(LCD_HOME);
		lcd_clear_row(FIRST_ROW);
	}
	else if (bType == DISPLAY_UART)
	{
		usartTransmitString(voltagePotenStr);
		usartTransmitString(" V ");
		usartTransmitString(" ");
		usartTransmitString(brightnessStr);
		usartTransmitString(" ");
		usartTransmitString(humidityStr);
		usartTransmitString("\n");
	}
}



ISR(ADC_vect)
{
	displayAllData(gPageCountLcd, DISPLAY_LCD);
	if (gPageCountLcd == LCD_PAGE_LIMIT)
	gPageCountLcd = LCD_PAGE_1;
	   
	gAdcValueCh[gAdcChCounter] = ADC; // Read the ADC value
	gAdcChCounter++;
	if (gAdcChCounter == 3)
	gAdcChCounter = 0;
	   
	ADMUX = gAdcCh[gAdcChCounter]; // Select the next channel
	ADCSRA |= (1 << ADSC); // Start the next conversion
}



int main(void)
{
	DDRB   |= (1<<PORTB5);
	PORTB  &= ~(1<<PORTB5);
				
	//USART_Init(MYUBRR);
	lcd_init();				// Lcd setup
	setupTim0Irq();			// Timer 0 for button debounce
	btnSetupIrq();			// External interrupt setup
	adcInit();				// Adc setup
	sei();
    while (1) 
    {

	
    }
	return 0;
}

