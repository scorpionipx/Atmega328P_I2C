/*
 * I2C.c
 *
 * Created: 26-Jan-18 10:50:14 PM
 *  Author: ScorpionIPX
 
 * Based on Atmel-42735B-ATmega328/P_Datasheet_Complete-11/2016
 */ 

#include "global.h"
#include <avr/io.h>
#include <util/twi.h>
#include "I2C.h"


void init_I2C_as_slave(unsigned char address)
{
	// TWI (Slave) Address Register
	TWAR = (address << 1) + 1; // load the 7bits address into the MSBs
	
	// TWI Control Register
	TWCR |= ((1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE)); // set TWI's Interrupt Flag, Enable Acknowledge, Enable and Interrupt Enable
}

void stop_I2C(void)
{
	// clear acknowledge and enable bits
	TWCR &= ~( (1<<TWEA) | (1<<TWEN) );
}

ISR(TWI_vect)
{
	switch(TW_STATUS)
	{
		case TW_SR_DATA_ACK:
		// received data from master, call the receive callback
		I2C_recv(TWDR);
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		case TW_ST_SLA_ACK:
		// master is requesting data, call the request callback
		I2C_req();
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		case TW_ST_DATA_ACK:
		// master is requesting data, call the request callback
		I2C_req();
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		case TW_BUS_ERROR:
		// some sort of erroneous state, prepare TWI to be readdressed
		TWCR = 0;
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		default:
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
	}
}