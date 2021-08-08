/*
 * Button_INT.h
 *
 * Created: 24-Jul-21 3:26:24 PM
 *  Author: ayman
 */ 


#ifndef BUTTON_INT_H_
#define BUTTON_INT_H_

void BUTTON_init();
sint8_t BUTTON_checkStatus(uint8_t ButtonNum);                                                

//buttons
#define BUTTON_CTRLPORT   PortB
#define ButtonCard    Pin2

//
#define ButtonError -1
#endif /* BUTTON_INT_H_ */