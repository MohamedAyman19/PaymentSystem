/*
 * App.c
 *
 * Created: 01-Aug-21 2:31:38 AM
 *  Author: ayman
 */ 

#include "APP.h"


uint8_t recieved;
uint8_t recievedspi;
uint8_t data[15];
uint8_t check[12];
uint8_t EEpromdata[5];
uint8_t EEpromPandata[10];
void System_Init()
{
	DIO_setPortDirection(PortA,OUTPUT);
	SPI_vdInit();
	I2C_Init(I2C_CH_0);
	EEPROM_Init(EEPROM_CH_0);
	UART_vdInit();
	if(EEPROM_Empty()==1)
	
	{
		UART_uint8_tSendString("Programming mode");
		Admin_Mode();
	}

}
void System_Update()
{
	

	if (SPI_UART_DataAvailable()==1)
	{
		Admin_Mode();
	}
	if(SPI_UART_DataAvailable()==2)
	{
		operation();
	}
}


uint8_t SPI_UART_DataAvailable()
{
	if(UART_IsDataReady())
	return 1;
	if(SPI_IsDataReady())
	return 2;
	return 0;
}

uint8_t Admin_Mode()
{
	UART_uint8_tGetString(data);
	if (!((data[0]=='A')&&(data[1]=='D')&&(data[2]=='M')&&(data[3]=='I')&&(data[4]=='N')))
	{
		UART_uint8_tSendString("wrong command");
		return 0;
	}
	else
	{
		
		do
		{
			data[9]='\0';
			UART_uint8_tSendString("Enter the PAN from 9 characters");
			UART_uint8_tGetString(data);
			if(data[9]!=13)
				UART_uint8_tSendString("wrong");
		} while ((data[9]!=13));

		data[9]='\0';
			EEPROM_WriteBytes(EEPROM_CH_0,MEMORY_BLOCK_1,0X08,data,10);
			EEPROM_ReadBytes(EEPROM_CH_0,MEMORY_BLOCK_1,0X08,EEpromPandata,10);
		
		do
		{
			data[4]='\0';
			UART_uint8_tSendString("Enter the PIN from four numbers");
			UART_uint8_tGetString(data);
			if((data[4]!=13)||(PIN_NotInteger(data)))
			UART_uint8_tSendString("wrong");
		}while((data[4]!=13)||(PIN_NotInteger(data)));
		UART_uint8_tSendString("Card is programmed successfully");
		data[4]='\0';
		
			EEPROM_WriteBytes(EEPROM_CH_0,MEMORY_BLOCK_1,0x02,data,5);
			EEPROM_ReadBytes(EEPROM_CH_0,MEMORY_BLOCK_1,0X02,EEpromdata,5);
		
	}
	
	return 0;
	
}

uint8_t operation()
{
	recievedspi=0;
	EEPROM_ReadBytes(EEPROM_CH_0,MEMORY_BLOCK_1,0X02,EEpromdata,5);
	EEPROM_ReadBytes(EEPROM_CH_0,MEMORY_BLOCK_1,0X08,EEpromPandata,10);
	uint8_t SPIdata[11];
	recievedspi=SPI_SlaveReceive(2);
	if(recievedspi=='P')
	{
		for(uint8_t i=0;i<4;i++)
		{
			data[i]=SPI_SlaveReceive('A');
		}
		for(uint8_t i=0;i<4;i++)
		{
			if(EEpromdata[i]!=data[i])
			{
				SPI_SlaveReceive(0);
				return 0;
			}
			
		}
		SPI_SlaveReceive(1);
		for(uint8_t i=0;i<9;i++)
		{
			data[i]=SPI_SlaveReceive(EEpromPandata[i]);
				if(data[i]=='W')
					return 0;
		}
	}

	return 0;
}
uint8_t PIN_NotInteger(uint8_t*Pin)
{
	for(uint8_t i=0;i<4;i++)
	{
		if((Pin[i]>'9')||(Pin[i]<'0'))
		{
			return 1;
		}
	}
	return 0;
}
uint8_t EEPROM_Empty()
{
	for(uint8_t i=0;i<9;i++)
	{
		EEPROM_Read(EEPROM_CH_0,MEMORY_BLOCK_1,(0x15+i),&(EEpromdata[i]));
		for(uint32_t j=0;j<50000;j++);
		if(EEpromdata[i]!=0xff)
		{
			return 0;
		}
	}
	for(uint8_t i=0;i<4;i++)
	{
		EEPROM_Read(EEPROM_CH_0,MEMORY_BLOCK_1,(0x02+i),&(EEpromdata[i]));
		for(uint32_t j=0;j<50000;j++);
		if(EEpromdata[i]!=0xff)
		{
			return 0;
		}
	}
	return 1;
}