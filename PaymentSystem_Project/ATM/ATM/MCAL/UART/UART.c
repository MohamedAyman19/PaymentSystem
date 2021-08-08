/*
 * UART.c
 *
 * Created: 25-Jul-21 1:29:23 PM
 *  Author: ayman
 */ 
#include "..\..\common_macros.h"
#include "..\..\compiler.h"
#include "UART.h"
#include "UART_Registers.h"
void UART_vdInit(void)
{
	// Set BaudRate  9600/8MhZ
	UBRRL_REGISTER=51;
	UBRRH_REGISTER=0;
	// Enable RX and TX
	UCSRB_REGISTER=0x18;
	// Set Frame Format -> 8 data, 1 stop, No Parity
	UCSRC_REGISTER=0x86;

}

void UART_vdSendByte(uint8_t data)
{
  // Wait until transmission Register Empty
  while(!(UCSRA_REGISTER&0x20));
  UDR_REGISTER = data;
}

uint8_t UART_uint8_tGetByte(void)
{
  uint8_t Result;
  // Wait for data to be received 
  while(!(UCSRA_REGISTER&0x80));
  Result = UDR_REGISTER;
  
  // Clear Flag 
  SET_BIT(UCSRA_REGISTER,7);
  return Result;
}
uint8_t UART_uint8_tSendString(unsigned char*data)
{
	for(uint8_t i=0;(data[i]!=13)&&(data[i]!='\0');i++)
	{
		UART_vdSendByte(data[i]);
	}
	UART_vdSendByte('\r');
	return 0;
}
void UART_uint8_tGetString(uint8_t*data)
{
	uint8_t i=0;
	do
	{
		
		data[i]=UART_uint8_tGetByte();
		if(data[i]==13)
		{
			data[i]='\0';
		}
		i++;
	
	}while(data[(i-1)]!='\0');

	
}
uint8_t UART_IsDataReady(void)
{
	if(!(UCSRA_REGISTER&0x80))
	return 0;
	return 1;
}