/*
 * App.h
 *
 * Created: 01-Aug-21 2:31:23 AM
 *  Author: ayman
 */ 


#ifndef APP_H_
#define APP_H_
#include "..\common_macros.h"
#include "..\compiler.h"
#include "..\MCAL\DIO\DIO.h"
#include "..\MCAL\UART\UART.h"
#include "..\MCAL\SPI\SPI.h"
#include "..\MCAL\I2C\I2C.h"
#include "..\HAL\EEPROM\EEPROM.h"

void System_Init(void);
void System_Update(void);
uint8_t EEPROM_DataAvailable(uint8_t);
uint8_t Admin_Mode();
uint8_t SPI_UART_DataAvailable();
uint8_t operation();
uint8_t PIN_NotInteger(uint8_t*data);
uint8_t EEPROM_Empty();


#endif /* APP_H_ */