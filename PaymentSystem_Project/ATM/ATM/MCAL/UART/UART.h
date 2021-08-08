/*
 * UART.h
 *
 * Created: 25-Jul-21 1:28:16 PM
 *  Author: ayman
 */ 


#ifndef UART_H_
#define UART_H_


void UART_vdInit(void);
void UART_vdSendByte(uint8_t data);
uint8_t UART_uint8_tGetByte(void);
void UART_uint8_tGetString(uint8_t*data);
uint8_t UART_uint8_tSendString(uint8_t*data);
uint8_t UART_IsDataReady(void);

#endif /* UART_H_ */