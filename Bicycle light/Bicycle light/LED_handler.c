#define LED_ON  PORTD |= 1<<PORTD1
#define LED_OFF  PORTD &= ~(1<<PORTD1)
#define LED_TOGGLE  PIND |= (1<<PIND1)*/

unsigned char FlashLightState = FLASHFASTBLINK;
DDRD |= (1<<DDD1); // PORTD pin1 is output for driving the power LED
