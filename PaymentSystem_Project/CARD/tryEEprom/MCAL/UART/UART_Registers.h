/*
 * UART_Registers.h
 *
 * Created: 25-Jul-21 2:45:47 PM
 *  Author: ayman
 */ 


#ifndef UART_REGISTERS_H_
#define UART_REGISTERS_H_
#define UBRRL_REGISTER  *( ( volatile uint8_t* ) 0x29)
#define UCSRB_REGISTER  *( ( volatile uint8_t* ) 0x2A)
#define UCSRA_REGISTER  *( ( volatile uint8_t* ) 0x2B)
#define UDR_REGISTER    *( ( volatile uint8_t* ) 0x2C)
#define UCSRC_REGISTER  *( ( volatile uint8_t* ) 0x40)
#define UBRRH_REGISTER  *( ( volatile uint8_t* ) 0x40)

#endif /* UART_REGISTERS_H_ */