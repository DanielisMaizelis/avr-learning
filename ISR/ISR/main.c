#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

void setSSLow() {
	// Drive SS to low
	PORTB &= ~(1<<PINB4);
}

void setSSHigh() {
	// Set SS to high
	PORTB |= (1<<PINB4);
}

void SPI_MasterInit(void)
{
	// Set SS, MOSI and SCK output, all others input
	DDRB = (1<<PINB4)|(1<<PINB5)|(1<<PINB7);
	setSSHigh();

	// Enable SPI, Master, set clock rate fck/128
	// Sample on rising edge, output on falling
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPR1)|(0<<CPHA)|(0<<CPOL);
}

char SPI_MasterTransmit(char cData)
{
	setSSHigh();
	// Start transmission
	SPDR = cData;
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF))) ;

	char receivedData = SPDR;
	setSSLow();
	return receivedData;
}

char buffer[3];

int main(void)
{
	//SPI_MasterInit();

	// Send 'Read JEDEC ID' command
	
	

	// Get data
	while(1)
	{
		setSSLow();
		
		for(int i=1; i<=0xF; i++)
		{
			char status = SPI_MasterTransmit(0x);
			char data = SPI_MasterTransmit(i);
			_delay_ms(0.1);
		}
		
		//buffer[i] = data;!
	}
	//setSSHigh();

	_delay_ms(1000);

	while (1) {
		// Do nothing
	}
}