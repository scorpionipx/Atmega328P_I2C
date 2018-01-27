/*
 * I2C.c
 *
 * Created: 26-Jan-18 10:29:58 PM
 * Author : ScorpionIPX
 */ 

#include "global.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "I2C.h"

#define ADDRESS 0x13 // address at witch uC responds as slave
#define BUILTIN_LED PB5

void init_uC(void);
void led_blink(void);

int main(void)
{
	init_uC();
	
    while (1) 
    {
		if(TEST_BLINK)
		{
			led_blink();	
		}
    }
}

void init_uC(void)
{
	
	DDRB = 0xFF; //PORTB output
	PORTB = 1 << BUILTIN_LED;
	
	TEST_BLINK = TRUE;
	init_I2C_as_slave(ADDRESS);
	
	sei(); // enable global interrupts
}

void led_blink(void)
{
	PORTB &= ~(1 << BUILTIN_LED);
	_delay_ms(50);
	PORTB = 1 << BUILTIN_LED;
	_delay_ms(150);
}