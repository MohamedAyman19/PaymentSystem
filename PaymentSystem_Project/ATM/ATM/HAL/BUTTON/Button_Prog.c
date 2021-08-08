/*
 * Button_Prog.c
 *
 * Created: 24-Jul-21 3:26:52 PM
 *  Author: ayman
 */ 

#include "..\..\compiler.h"
#include "..\..\common_macros.h"
#include "..\..\MCAL\DIO\DIO.h"
#include "Button_INT.h"

void BUTTON_init()
{
	DIO_setPinDirection(BUTTON_CTRLPORT,Pin2,INPUT);
}
sint8_t BUTTON_checkStatus(uint8_t ButtonNum)
{
	//uint8_t *value;
	if(ButtonNum<=Pin7)
	{
		//DIO_readPin(PINB,ButtonNum,value);
		 return((BIT_IS_SET(PINB,ButtonNum)));
		/*if((*value)==1)
		{
			//for(uint32_t i=0;i<72000;i++); ///                           for debouncing
			if((*value)==1)
			{
				return 1;
			}

		}
		return 0;*/
		
	}

	return  ButtonError;
}