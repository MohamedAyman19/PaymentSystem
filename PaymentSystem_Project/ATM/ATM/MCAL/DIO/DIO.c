/*
 * DIO.c
 *
 *
 *      Author: Bishoy Nabil
 */


#include "DIO.h"


E_STATUS DIO_setPinDirection(uint8_t port, uint8_t pin, uint8_t dir)
{
	E_STATUS u8_State=ERROR;
	if(((port>=PortA)&&(port<=PortD))&&((pin<=Pin7)&&(pin>=Pin0))){
		u8_State=Success;
		switch(port)
		{
		case PortA:
		{
			if(dir==INPUT)
				CLEAR_BIT(DDRA,pin);
			else
				SET_BIT(DDRA,pin);
		}
		break;
		case PortB:
		{
			if(dir==INPUT)
				CLEAR_BIT(DDRB,pin);
			else
				SET_BIT(DDRB,pin);
		}
		break;
		case PortC:
		{
			if(dir==INPUT)
				CLEAR_BIT(DDRC,pin);
			else
				SET_BIT(DDRC,pin);
		}
		break;
		case PortD:
		{
			if(dir==INPUT)
				CLEAR_BIT(DDRD,pin);
			else
				SET_BIT(DDRD,pin);
		}
		break;
		}
	}
	return u8_State;
}

E_STATUS DIO_setPortDirection(uint8_t port, uint8_t dir)
{
	E_STATUS u8_State=ERROR;
	if((port>=PortA)&&(port<=PortD)){
		u8_State=Success;
		switch(port)
		{
		case PortA:
		{
			if(dir==OUTPUT)
			{
				DDRA=OUTPUT_PORT;
			}else
				DDRA=INPUT_PORT;
		}
		break;
		case PortB:
		{
			if(dir==OUTPUT)
			{
				DDRB=OUTPUT_PORT;
			}else
				DDRB=INPUT_PORT;
		}
		break;
		case PortC:
		{
			if(dir==OUTPUT)
			{
				DDRC=OUTPUT_PORT;
			}else
				DDRC=INPUT_PORT;
		}
		break;
		case PortD:
		{
			if(dir==OUTPUT)
			{
				DDRD=OUTPUT_PORT;
			}else
				DDRD=INPUT_PORT;
		}
		break;
		}
	}
	return u8_State;
}


E_STATUS DIO_togglePin(uint8_t port, uint8_t pin)
{
	E_STATUS u8_State=ERROR;
	if(((port>=PortA)&&(port<=PortD))&&((pin<=Pin7)&&(pin>=Pin0))){
		u8_State=Success;
		switch(port)
		{
		case PortA:
			TOGGLE_BIT(PORTA,pin);
			break;
		case PortB:
			TOGGLE_BIT(PORTB,pin);
			break;
		case PortC:
			TOGGLE_BIT(PORTC,pin);
			break;
		case PortD:
			TOGGLE_BIT(PORTD,pin);
			break;
		}

	}
	return u8_State;
}


E_STATUS DIO_readPin(uint8_t port, uint8_t pin, uint8_t * value)
{
	E_STATUS u8_State=ERROR;
	if(((port>=PortA)&&(port<=PortD))&&((pin<=Pin7)&&(pin>=Pin0))){
		u8_State=Success;
		switch(port)
		{
		case PortA:
			*value=BIT_READ(PORTA,pin);
			break;
		case PortB:
			*value=BIT_READ(PORTB,pin);
			break;
		case PortC:
			*value=BIT_READ(PORTC,pin);
			break;
		case PortD:
			*value=BIT_READ(PORTD,pin);
			break;
		}
	}
	return u8_State;
}


E_STATUS DIO_readPort(uint8_t port, uint8_t * value)
{
	E_STATUS u8_State=ERROR;
	if((port>=PortA)&&(port<=PortD)){
		u8_State=Success;
		switch(port)
		{
		case PortA:
			*value=PINA;
			break;
		case PortB:
			*value=PINB;
			break;
		case PortC:
			*value=PINC;
			break;
		case PortD:
			*value=PIND;
			break;
		}
	}
	return u8_State;
}


E_STATUS DIO_writePin(uint8_t port, uint8_t pin, uint8_t data)
{
	E_STATUS u8_State=ERROR;
	if(((port>=PortA)&&(port<=PortD))&&((pin<=Pin7)&&(pin>=Pin0))){
		u8_State=Success;
		switch(port)
		{
		case PortA:
		{
			if(data==HIGH)
				SET_BIT(PORTA,pin);
			else
				CLEAR_BIT(PORTA,pin);
		}
		break;
		case PortB:
		{
			if(data==HIGH)
				SET_BIT(PORTB,pin);
			else
				CLEAR_BIT(PORTB,pin);
		}
		break;
		case PortC:
		{
			if(data==HIGH)
				SET_BIT(PORTC,pin);
			else
				CLEAR_BIT(PORTC,pin);
		}
		break;
		case PortD:
		{
			if(data==HIGH)
				SET_BIT(PORTD,pin);
			else
				CLEAR_BIT(PORTD,pin);
		}
		break;
		}
	}
	return u8_State;
}


E_STATUS DIO_writePort(uint8_t port, uint8_t data)
{
	E_STATUS u8_State=ERROR;
	if((port>=PortA)&&(port<=PortD)){
		u8_State=Success;
		switch(port)
		{
		case PortA:
			PORTA=data;
			break;
		case PortB:
			PORTB=data;
			break;
		case PortC:
			PORTC=data;
			break;
		case PortD:
			PORTD=data;
			break;
		}
	}
	return u8_State;
}

