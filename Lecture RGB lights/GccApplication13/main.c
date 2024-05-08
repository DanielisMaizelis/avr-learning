/*
* Light_WS2812 library example - RGB_blinky
*
* cycles one LED through red, green, blue
*
* This example is configured for a ATtiny85 with PLL clock fuse set and
* the WS2812 string connected to PB4.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

struct cRGB led[257];

int main(void)
{
/*
  #ifdef __AVR_ATtiny10__
  CCP=0xD8;		// configuration change protection, write signature
  CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
  #endif

  while(1)
  {
	  for(int i = 2; i < 258; i++) 
	  {
		leds(i-2,0,0,0);
		leds(i-1,0,255,0);
		leds(i,0,255,0);
		leds(i+1,0,0,0);
		
		_delay_ms(500);
		ws2812_setleds(led,256);
		_delay_ms(00);                         // wait for 500ms.
	  }
  }*/

	coordinates(2,2,0,0,255);
	coordinates(-3,-3,0,255,0);
	coordinates(8,-8,255,0,0);
	coordinates(-1,-1,0,0,255);
	ws2812_setleds(led,256);
	
}


void coordinates(int x, int y, int red, int green, int blue)
{
	int position;
	
	if(x>0 && y<0)
	{
		position = 8+x+(8-(y*-1))*16;
	}
	else if (x<0 && y>0)
	{
		position = 129+8-(x*-1)+(y-1)*16;
	}
	else if (x<0 && y<0)
	{
		position =9-(x*-1)+(8-(y*-1))* 16;
	}
	else if (x>0 && y>0)
	{
		position= 136+x+(y-1)*16;
	}
	set_leds(position,red,green,blue,x);
}

void set_leds(int position, int red, int green, int blue, int x)
{
	int corrected_position;
	if ((position>=17 && position<=32) || (position>=49 && position<=64) || (position>=81 && position<= 96) || (position>=113 && position<= 128) || (position>=145 && position<= 160) || (position>=177 && position<= 192) || (position>=209 && position<= 224) || (position>=241 && position<= 256))
	{
		if(x>0)
		{
			corrected_position = position-(x*2-1);
		}
		else
		{	
			corrected_position = position+((x*-1)*2-1);
		}
	}
	corrected_position-=1;
	led[corrected_position].r=red;led[corrected_position].g=green;led[corrected_position].b=blue;    // Write red to array
}