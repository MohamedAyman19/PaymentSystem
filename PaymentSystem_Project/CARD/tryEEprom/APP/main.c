/*
 * tryEEprom.c
 *
 * Created: 01-Aug-21 1:50:02 AM
 * Author : ayman
 */ 

#define F_CPU 8000000UL

#include "APP.h"



int main(void)
{
	//volatile int x;
/*	int ayman[10];
	I2C_Init(I2C_CH_0);
	EEPROM_Init(EEPROM_CH_0);
	UART_vdInit();*/
	
	System_Init();
    /* Replace with your application code */
    while (1) 
    {
		/*
		EEPROM_Write(EEPROM_CH_0,MEMORY_BLOCK_1,0x01,50);
		for(uint32_t i=0;i<100000;i++);
		EEPROM_Read(EEPROM_CH_0,MEMORY_BLOCK_1,0x01,&(ayman[0]));
		for(uint32_t i=0;i<100000;i++);
		UART_vdSendByte((ayman[0]));*/
		
		
		System_Update();
    }
}

