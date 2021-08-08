/*
 * APP.h
 *
 * Created: 06-Aug-21 12:33:57 AM
 *  Author: ayman
 */ 


#ifndef APP_H_
#define APP_H_

#include "..\MCAL\ADC\adc.h"
#include "..\HAL\LCD\lcd.h"
#include "..\HAL\DC_MOTOR\DC_Motor.h"
#include "..\Delay.h"
#include "..\MCAL\DIO\DIO.h"
#include "..\HAL\EEPROM\EEPROM.h"
#include "..\MCAL\I2C\I2C.h"
#include "..\HAL\KEYPAD\keypad.h"
#include "..\MCAL\SPI\SPI.h"
#include "..\MCAL\UART\UART.h"
#include "..\HAL\BUTTON\Button_INT.h"
#include "admin.h"
#define EMPTY 1
#define NOT_EMPTY 0

uint8_t EEPROM_EmptyCheck();
uint8_t SPI_UART_DataAvailable();
void customerEntry();
void maxAmountEntry();
uint8_t System_Update();
void operatingMode();
void displayTemp();
void InsertCard();
void System_Init();
float32_t serverCheck(uint8_t * recPan);


#endif /* APP_H_ */