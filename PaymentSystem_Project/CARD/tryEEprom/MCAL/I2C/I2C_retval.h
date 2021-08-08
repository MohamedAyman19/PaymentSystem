/*
 * I2C_retval.h
 *
 * Created: 7/16/2021 9:32:14 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __I2C_RETVAL_H__
#define __I2C_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "..\..\compiler.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t I2C_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_I2C_SUCCESS                    (I2C_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a function got a null pointer.
*/
#define           E_I2C_NULL_PTR                   (I2C_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a function got an invalid I2C channel.
*/
#define           E_I2C_INVALID_CH                 (I2C_ERROR_state_t)( 2 )

/**
* @brief: This return value indicate that a write collision occurred on writing
* to the data register.
*/
#define           E_I2C_WRITE_COLLISION            (I2C_ERROR_state_t)( 3 )

#endif /* __I2C_RETVAL_H__ */
