/*
 * I2C.h
 *
 * Created: 26-Jan-18 10:50:45 PM
 *  Author: ScorpionIPX
 */ 


#ifndef I2C_H_
#define I2C_H_

void init_I2C_as_slave(unsigned char address);
void stop_I2C(void);

volatile uint8_t buffer_address;
volatile uint8_t txbuffer[0xFF];
volatile uint8_t rxbuffer[0xFF];
ISR(TWI_vect);

#endif /* I2C_H_ */