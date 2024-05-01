 #include "ledblink.h"
 #include <avr/io.h>
 
 void led_init(){
	 DDRD |= (1<<DDD1); // PORTD pin1 is output for driving the power LED
 }
 
 void led_off(){
	 LED_OFF;
 }
 
 void led_on(){
	 LED_ON;
 }
 
 void led_toggle(){
	 LED_TOGGLE;
 }