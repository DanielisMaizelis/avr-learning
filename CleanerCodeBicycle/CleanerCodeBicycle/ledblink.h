
#ifndef LEDBLINK_H_
#define LEDBLINK_H_

#define LED_ON  PORTD |= 1<<PORTD1
#define LED_OFF  PORTD &= ~(1<<PORTD1)
#define LED_TOGGLE  PIND |= (1<<PIND1)

void led_init();
void led_off();
void led_on();
void led_toggle();

#endif /* LEDBLINK_H_ */