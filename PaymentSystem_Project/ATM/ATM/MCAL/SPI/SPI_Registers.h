/*
 * SPI_Registers.h
 *
 * Created: 28-Jul-21 10:51:13 AM
 *  Author: ayman
 */ 


#ifndef SPI_REGISTERS_H_
#define SPI_REGISTERS_H_


#define SPCR *( ( volatile uint8_t* ) 0x2D )
#define SPSR *( ( volatile uint8_t* ) 0x2E )
#define SPDR *( ( volatile uint8_t* ) 0x2F )


#endif /* SPI_REGISTERS_H_ */