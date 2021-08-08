/*
 * EEPROM_retval.h
 *
 * Created: 7/20/2021 10:53:35 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __EEPROM_RETVAL_H__
#define __EEPROM_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "..\..\compiler.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t EEPROM_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_EEPROM_SUCCESS           (EEPROM_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a function
* got an invalid channel number.
*/
#define           E_EEPROM_INVALID_CH_NO     (EEPROM_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a function
* from I2C driver returned an error.
*/
#define           E_EEPROM_I2C_ERROR         (EEPROM_ERROR_state_t)( 2 )

/**
* @brief: This return value indicate that the READ/WRITE function
* got an invalid address in the EEPROM.
*/
#define           E_EEPROM_INVALID_ADDRESS   (EEPROM_ERROR_state_t)( 3 )

/**
* @brief: This return value indicate that a function
* got an uninitialized pointer.
*/
#define           E_EEPROM_NULL_PTR          (EEPROM_ERROR_state_t)( 4 )

#endif /* __EEPROM_RETVAL_H__ */
