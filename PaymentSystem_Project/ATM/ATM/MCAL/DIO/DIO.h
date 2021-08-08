/*
 * DIO.h
 *
 *
 *      Author: Bishoy Nabil
 */

#ifndef DIO_H_
#define DIO_H_

#include "DIO_registers.h"
#include "..\..\compiler.h"
#include "..\..\common_macros.h"

typedef sint8_t E_STATUS;

#define ERROR  -1
#define Success  1
#define INPUT  0
#define OUTPUT  1
#define INPUT_PORT 0x00
#define OUTPUT_PORT 0xFF
#define LOW  0
#define HIGH  1


typedef enum {
	Pin0,
	Pin1,
	Pin2,
	Pin3,
	Pin4,
	Pin5,
	Pin6,
	Pin7
}EN_PIN_t;

typedef enum{
	PortA,
	PortB,
	PortC,
	PortD
}EN_PORT_t;



/* API's */

E_STATUS DIO_setPinDirection(uint8_t port, uint8_t pin, uint8_t dir);
E_STATUS DIO_setPortDirection(uint8_t port, uint8_t dir);
E_STATUS DIO_togglePin(uint8_t port, uint8_t pin);
E_STATUS DIO_readPin(uint8_t port, uint8_t pin, uint8_t *value);
E_STATUS DIO_readPort(uint8_t port, uint8_t * value);
E_STATUS DIO_writePin(uint8_t port, uint8_t pin, uint8_t data);
E_STATUS DIO_writePort(uint8_t port, uint8_t data);


#endif /* DIO_H_ */
