/*
 * SPI.h
 *
 * Created: 28-Jul-21 10:46:47 AM
 *  Author: ayman
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_vdInit(void);
uint8_t SPI_MasterTransmit(uint8_t cData);
uint8_t SPI_SlaveReceive(uint8_t cData);
uint8_t SPI_IsDataReady(void);


#endif /* SPI_H_ */