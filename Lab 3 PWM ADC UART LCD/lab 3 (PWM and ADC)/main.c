#include "main.h"
volatile uint16_t result;
	
	
void lcdInit();



ISR(ADC_vect)
{
	result = ADC;
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


void getVoltage()
{
	ADCSRA |= (1 << ADSC)|(1<< ADIE); // Start adc interrupts and adc 
	char msg[10];
	char msg3[10];
	
	float resultf    = (float)(result/1024.0)*100;
	uint8_t resultInt = (uint8_t)resultf;
	
	
	float_to_string((result*5.0)/1024.0, msg, 3);
	sprintf(msg3, "%d", (uint8_t)resultInt);
	strcat(msg," V ");
	strcat(msg, msg3);
	strcat(msg, "%");
	
	displayVoltageLcd(msg);
	_delay_ms(100);						 // Intentional Delay
	clearScreen();
	//usartTransmitString(msg);
	ADCSRA &= ~((1 << ADSC)|(1<< ADIE)); // Stop adc interrupts and adc	
}




int main(void)
{

	// Setup usart
	//USART_Init(MYUBRR);
	lcdInit();
	//adcSetup();
	sei();
	
		
    while (1) 
    {
		//PORTB |= (1<<PORTB5);
		//PORTB |= (1<<PORTB2);
	
	
		float resultf     = (float)(result/1024.0)*100;
		uint8_t resultInt = (uint8_t)resultf;
		getVoltage();
		/*
		//fastPwmTim0(resultInt);
		fastPwmTim1(resultInt);
		
		*/	
    }
}

