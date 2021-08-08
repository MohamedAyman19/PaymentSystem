/*
 * EEPROM.c
 *
 * Created: 7/20/2021 10:53:52 AM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "EEPROM.h"
/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function initializes an EEPROM channel.
*
* @param [in]  EEPROM_CH   -  EEPROM channel number.
*
* @return function error state.
*/
EEPROM_ERROR_state_t EEPROM_Init(uint8_t EEPROM_CH)
{
   I2C_ERROR_state_t e_state;
   
   uint8_t u8_I2C_CH;
   
   switch(EEPROM_CH)
   {
      #ifdef EEPROM_CH_0
      case EEPROM_CH_0:
         u8_I2C_CH = EEPROM_CH_0_I2C_CH;
         break;
      #endif
      default:
         return E_EEPROM_INVALID_CH_NO;
   }
   
   /* configure i2c pins */
   e_state = I2C_Init(u8_I2C_CH);
   /* make sure pin configuration is successful */
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }
   
   /* return success message */
   return E_EEPROM_SUCCESS;
}

/**
* @brief: This function reads from an EEPROM memory block.
*
* @param [in]  EEPROM_CH   -  EEPROM channel number.
* @param [in]  memoryBlock -  Memory block to write to.
* @param [in]  address     -  Address to read from.
* @param [out] data        -  Pointer to where to store received data.
*
* @return function error state.
*/
EEPROM_ERROR_state_t EEPROM_Read(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t address, uint8_t * data)
{
   I2C_ERROR_state_t e_state;
   
   uint8_t u8_I2C_CH;
   
   switch(EEPROM_CH)
   {
      #ifdef EEPROM_CH_0
      case EEPROM_CH_0:
         u8_I2C_CH = EEPROM_CH_0_I2C_CH;
         break;
      #endif
      default:
         return E_EEPROM_INVALID_CH_NO;
   }

   /* Set start condition */
   e_state =I2C_Start(u8_I2C_CH);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* Set first memory block address + W */
   e_state = I2C_Write(u8_I2C_CH, memoryBlock);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* Set address to read from */
   e_state = I2C_Write(u8_I2C_CH, address);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* repeated start */
   e_state = I2C_RepeatedStart(u8_I2C_CH);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* Set first memory block address + R */
   e_state= I2C_Write(u8_I2C_CH, memoryBlock | 1 );
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* receive data in the address */
   e_state = I2C_ReadNoAck(u8_I2C_CH, data);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* release the bus */
   e_state = I2C_Stop(u8_I2C_CH);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }
   
   /* return success message */
   return E_EEPROM_SUCCESS;
}

/**
* @brief: This function writes an EEPROM memory block.
*
* @param [in]  EEPROM_CH   -  EEPROM channel number.
* @param [in]  memoryBlock -  Memory block to write to.
* @param [in]  address     -  Address to write to.
* @param [in]  data        -  Data to write.
*
* @return function error state.
*/
EEPROM_ERROR_state_t EEPROM_Write(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t address, uint8_t data)
{
   I2C_ERROR_state_t e_state;
   uint8_t u8_I2C_CH;
   
   switch(EEPROM_CH)
   {
      #ifdef EEPROM_CH_0
      case EEPROM_CH_0:
         u8_I2C_CH = EEPROM_CH_0_I2C_CH;
         break;
      #endif
      default:
         return E_EEPROM_INVALID_CH_NO;
   }
   /* Set start condition */
   e_state = I2C_Start(u8_I2C_CH);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* Set first memory block address + W */
   e_state = I2C_Write(u8_I2C_CH, memoryBlock);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* set address to write to */
   e_state = I2C_Write(u8_I2C_CH, address);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* writes data to the address */
   e_state = I2C_Write(u8_I2C_CH, data);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* release the bus */
   e_state = I2C_Stop(u8_I2C_CH);
   if(E_I2C_SUCCESS != e_state)
   {
      return E_EEPROM_I2C_ERROR;
   }

   /* return success message */
   return E_EEPROM_SUCCESS;
}

/**
* @brief: This function writes an EEPROM memory block.
*
* @param [in]  EEPROM_CH   -  EEPROM channel number.
* @param [in]  memoryBlock -  Memory block to write to.
* @param [in]  address     -  Address to write to.
* @param [out] data        -  Pointer to where to store received data.
* @param [in]  bytes_num   -  number of bytes to read.
*
* @return function error state.
*/
EEPROM_ERROR_state_t EEPROM_ReadBytes(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t start_address, uint8_t * data, uint8_t bytes_num)
{
   I2C_ERROR_state_t e_state;
   
   for(uint8_t au8_BytesCounter = 0 ; au8_BytesCounter < bytes_num; au8_BytesCounter++)
   {
      e_state = EEPROM_Read(EEPROM_CH, memoryBlock, (start_address + au8_BytesCounter), &data[au8_BytesCounter]);
      if(E_I2C_SUCCESS != e_state)
      {
         return E_EEPROM_I2C_ERROR;
      }
   }
   
   /* return success message */
   return E_EEPROM_SUCCESS;
}

/**
* @brief: This function writes an EEPROM memory block.
*
* @param [in]  EEPROM_CH   -  EEPROM channel number.
* @param [in]  memoryBlock -  Memory block to write to.
* @param [in]  address     -  Address to write to.
* @param [in]  data        -  Data to write.
* @param [in]  bytes_num   -  number of bytes to write.
*
* @return function error state.
*/
EEPROM_ERROR_state_t EEPROM_WriteBytes(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t start_address, uint8_t * data, uint8_t bytes_num)
{
   I2C_ERROR_state_t e_state;
   
   for(uint8_t au8_BytesCounter = 0 ; au8_BytesCounter < bytes_num; au8_BytesCounter++)
   {
      e_state = EEPROM_Write(EEPROM_CH, memoryBlock, (start_address + au8_BytesCounter), data[au8_BytesCounter]);
      if(E_I2C_SUCCESS != e_state)
      {
         return E_EEPROM_I2C_ERROR;
      }
      dummy_delay();
      dummy_delay();
	  dummy_delay();
   }
   
   /* return success message */
   return E_EEPROM_SUCCESS;
   
}
