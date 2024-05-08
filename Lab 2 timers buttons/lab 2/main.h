#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000		 // CPU speed in Hz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define POLLING_MODE_1SEC 15625
#define RED_LED			  PORTB5
#define YELLOW_LED		  PORTB6
#define GREEN_LED		  PORTB7

typedef enum lightStates
{
	STOP,
	PREPARE,
	GO,
	STOP_IF_NOT_SAFE,
}lightStates_t;


void pinSetup(void); // Led's
void btnSetupIrq(void);
void btnPolling(void);
void setupTim0Irq(void);
void pollTim1Blink(void);
void setupTim1Irq(void);
void setupTim1Polling(void); // Task 1

#endif /* MAIN_H_ */