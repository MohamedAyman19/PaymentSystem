/*
 * I2C.c
 *
 * Created: 7/16/2021 9:32:59 AM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "I2C.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static Ptr_VoidFuncVoid_t g_Callback[I2C_NUMBERS];

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function initialize I2C channel.
*
* @param [in]  I2C_CH   -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Init(uint8_t I2C_CH)
{
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CControlR;
   volatile uint8_t * ptr_I2CStatusR;
   volatile uint8_t * ptr_I2CBitRateR;
   
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CControlR = &I2C_CONTROL_R;
         ptr_I2CStatusR = &I2C_STATUS_R;
         ptr_I2CBitRateR = &I2C_BIT_RATE_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* set pre-scalar value */
   *ptr_I2CStatusR = I2C_CH_0_PRESCALER;

   /* set bit rate */
   *ptr_I2CBitRateR = I2C_CH_0_BIT_RATE;

   /* set control configuration */
   *ptr_I2CControlR = I2C_CH_0_CONTROL_MASK;
   
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function sets the I2C slave address in slave nodes.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [in]  SlaveAddr   -  Slave Address.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_SetSlaveAddress(uint8_t I2C_CH, uint8_t SlaveAddr)
{
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CSlaveAddrR;

   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CSlaveAddrR = &I2C_SLAVE_ADDR_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* set slave address */
   *ptr_I2CSlaveAddrR = SlaveAddr;
   
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function sets a start condition on the bus.
*
* @param [in]  I2C_CH      -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Start(uint8_t I2C_CH)
{
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CControlR;
   
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CControlR = &I2C_CONTROL_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* clear interrupt flag and set start condition */
   *ptr_I2CControlR = (I2C_INTERRUPT_FLAG| I2C_START_BIT | I2C_EN);

   /* loop until interrupt flag is raised */
   while (!(*ptr_I2CControlR & I2C_INTERRUPT_FLAG));
   
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function sets a repeated start condition on the bus.
*
* @param [in]  I2C_CH      -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_RepeatedStart(uint8_t I2C_CH)
{
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CControlR;
   
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CControlR = &I2C_CONTROL_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* clear interrupt flag and set start condition */
   *ptr_I2CControlR |= (I2C_INTERRUPT_FLAG | I2C_START_BIT);
   /* loop until interrupt flag is raised */
   while (!(*ptr_I2CControlR & I2C_INTERRUPT_FLAG));
   
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function write a byte on I2C bus.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [in]  Data        -  data byte to be sent.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Write(uint8_t I2C_CH, uint8_t Data)
{
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CControlR;
   volatile uint8_t * ptr_I2CDataR;
   
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CDataR = &I2C_DATA_R;
         ptr_I2CControlR = &I2C_CONTROL_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* store data in the data register */
   *ptr_I2CDataR = Data;
   /* start sending the data bits */
   *ptr_I2CControlR = (I2C_INTERRUPT_FLAG | I2C_EN);
   /* loop until interrupt flag is raised */
   while (!(*ptr_I2CControlR & I2C_INTERRUPT_FLAG));
   
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function read a byte from I2C and sends an ack.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [out] Data        -  pointer to where to store the read data.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_ReadAck(uint8_t I2C_CH, uint8_t * Data)
{
   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == Data)
   {
      return E_I2C_NULL_PTR;
   }
   
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CControlR;
   volatile uint8_t * ptr_I2CDataR;
   
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CDataR = &I2C_DATA_R;
         ptr_I2CControlR = &I2C_CONTROL_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* start receiving and send ack at end. */
   *ptr_I2CControlR |= (I2C_INTERRUPT_FLAG | I2C_ACK_EN);
   /* loop until interrupt flag is raised */
   while (!(*ptr_I2CControlR & I2C_INTERRUPT_FLAG));
   /* return data received */
   *Data = *ptr_I2CDataR;
   
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function read a byte from I2C and doesn't send an ack.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [out] Data        -  pointer to where to store the read data.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_ReadNoAck(uint8_t I2C_CH, uint8_t * Data)
{
   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == Data)
   {
      return E_I2C_NULL_PTR;
   }
   
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CControlR;
   volatile uint8_t * ptr_I2CDataR;
   
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CDataR = &I2C_DATA_R;
         ptr_I2CControlR = &I2C_CONTROL_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* start receiving and don't send ack at end. */
   *ptr_I2CControlR |= (I2C_INTERRUPT_FLAG);
   /* loop until interrupt flag is raised */
   while (!(*ptr_I2CControlR & I2C_INTERRUPT_FLAG));
   /* return data received */
   *Data = *ptr_I2CDataR;
   
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function sets a stop condition on the bus.
*
* @param [in]  I2C_CH      -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Stop(uint8_t I2C_CH)
{
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CControlR;
   
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CControlR = &I2C_CONTROL_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* set stop condition */
   *ptr_I2CControlR = (I2C_INTERRUPT_FLAG | I2C_EN | I2C_STOP_BIT);
   
   while (*ptr_I2CControlR & I2C_STOP_BIT);
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function receives a stream of characters through I2C.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [out] Status      -  pointer to where to store the status of I2C.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Status(uint8_t I2C_CH, uint8_t * Status)
{
   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == Status)
   {
      return E_I2C_NULL_PTR;
   }
   
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CStatusR;
   
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CStatusR = &I2C_STATUS_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* return status */
   *Status = (*ptr_I2CStatusR & I2C_STATUS_BITS);
         
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function enables I2C interrupt.
*
* @param [in]  I2C_CH      -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_EnableInterrupt(uint8_t I2C_CH)
{
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CControlR;
   
   /* get the required I2C data */
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CControlR = &I2C_CONTROL_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* enable interrupt */
   *ptr_I2CControlR |= I2C_INTERRUPT_EN;
   
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function disables I2C interrupt.
*
* @param [in]  I2C_CH      -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_DisableInterrupt(uint8_t I2C_CH)
{
   /* variable to store the addresses of the required channel */
   volatile uint8_t * ptr_I2CControlR;
   
   /* get the required I2C data */
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         ptr_I2CControlR = &I2C_CONTROL_R;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* disable interrupt */
   *ptr_I2CControlR &= ~(I2C_INTERRUPT_EN);
   
   /* return success message */
   return E_I2C_SUCCESS;
}

/**
* @brief: This function sets a callback function.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [in]  Callback    -  address of the callback function.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_SetCallback(uint8_t I2C_CH, Ptr_VoidFuncVoid_t Callback)
{
   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == Callback)
   {
      return E_I2C_NULL_PTR;
   }
   
   /* variable to store the addresses of the required channel */
   volatile uint8_t u8_I2CIndex;
   
   /* get the required I2C data */
   switch(I2C_CH)
   {
      #ifdef I2C_CH_0
      case I2C_CH_0:
         u8_I2CIndex = I2C_CH_0;
         break;
      #endif
      default:
         return E_I2C_INVALID_CH;
   }
   
   /* set callback function to the required channel */
   g_Callback[u8_I2CIndex] = Callback;
   
   /* return success status */
   return E_I2C_SUCCESS;
}
