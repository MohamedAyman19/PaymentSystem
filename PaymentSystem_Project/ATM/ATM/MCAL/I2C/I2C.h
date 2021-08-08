/*
 * I2C.h
 *
 * Created: 7/16/2021 9:32:00 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __I2C_H__
#define __I2C_H__

/*- INCLUDES -----------------------------------------------*/
#include "..\..\compiler.h"
#include "I2C_Registers.h"
#include "I2C_retval.h"
#include "I2C_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* initialize I2C */
I2C_ERROR_state_t I2C_Init(uint8_t I2C_CH);

/* initialize I2C slave address */
I2C_ERROR_state_t I2C_SetSlaveAddress(uint8_t I2C_CH, uint8_t SlaveAddr);

/* put on bus start condition */
I2C_ERROR_state_t I2C_Start(uint8_t I2C_CH);

/* put on bus repeated start condition */
I2C_ERROR_state_t I2C_RepeatedStart(uint8_t I2C_CH);

/* sends a byte of data on bus */
I2C_ERROR_state_t I2C_Write(uint8_t I2C_CH, uint8_t Data);

/* reads from bus and sends acknowledgment bit */
I2C_ERROR_state_t I2C_ReadAck(uint8_t I2C_CH, uint8_t * Data);

/* reads from bus and don't send acknowledgment bit */
I2C_ERROR_state_t I2C_ReadNoAck(uint8_t I2C_CH, uint8_t * Data);

/* put on bus stop condition */
I2C_ERROR_state_t I2C_Stop(uint8_t I2C_CH);

/* return I2C status */
I2C_ERROR_state_t I2C_Status(uint8_t I2C_CH, uint8_t * Status);

/* enable I2C interrupts */
I2C_ERROR_state_t I2C_EnableInterrupt(uint8_t I2C_CH);

/* disable I2C interrupts */
I2C_ERROR_state_t I2C_DisableInterrupt(uint8_t I2C_CH);

/* set callback function */
//I2C_ERROR_state_t I2C_SetCallback(uint8_t I2C_CH, Ptr_VoidFuncVoid_t Callback);

#endif /* __I2C_H__ */
