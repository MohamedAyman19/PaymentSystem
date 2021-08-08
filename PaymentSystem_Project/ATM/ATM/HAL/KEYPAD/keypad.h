 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Author: Bishoy Nabil
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "..\..\compiler.h"
#include "..\..\micro_config.h"
#include "..\..\common_macros.h"
#include "..\..\MCAL\DIO\DIO.h"

/*******************************************************************************
 *                     				 Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA 

/*******************************************************************************
 *              				         APIs                                   *
 *******************************************************************************/

/* Function responsible for getting the pressed keypad key */
uint8_t KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
