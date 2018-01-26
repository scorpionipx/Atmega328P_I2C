/*
 * I2C.c
 *
 * Created: 26-Jan-18 10:29:58 PM
 * Author : ScorpionIPX
 */ 

#define F_CPU 16000000UL // ProMini runs using an external Quartz crystal oscillator @ 16MHz
#define ADDRESS 0x13 // address at witch uC responds as slave

#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#define BUILTIN_LED PB5

void init_uC(void);
void led_blink(void);

int main(void)
{
	init_uC();
	
    while (1) 
    {
		//led_blink();
    }
}

void init_uC(void)
{
	
	DDRB = 0xFF; //PORTB output
	PORTB = 1 << BUILTIN_LED;
	
	init_I2C_as_slave(ADDRESS);
}

void led_blink(void)
{
	PORTB &= ~(1 << BUILTIN_LED);
	_delay_ms(100);
	PORTB = 1 << BUILTIN_LED;
	_delay_ms(500);
}