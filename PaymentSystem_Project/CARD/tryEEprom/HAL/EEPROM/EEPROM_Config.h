/*
 * EEPROM_Config.h
 *
 * Created: 7/20/2021 10:53:45 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __EEPROM_CONFIG_H__
#define __EEPROM_CONFIG_H__

/*- INCLUDES -----------------------------------------------*/
#include "..\..\utils.h"
#include "..\..\compiler.h"
/*- MACROS -------------------------------------------------*/

#define MEMORY_BLOCK_1                       (uint8_t)(0XA0)
#define MEMORY_BLOCK_2                       (uint8_t)(0XA2)
#define MEMORY_BLOCK_3                       (uint8_t)(0XA4)
#define MEMORY_BLOCK_4                       (uint8_t)(0XA6)
#define MEMORY_BLOCK_5                       (uint8_t)(0XA8)

#define EEPROM_CH_0                 (uint8_t)(1)
#define EEPROM_CH_0_I2C_CH          I2C_CH_0

#define EEPROM_MAX_MEMORY_BLOCKS    (uint8_t)(7)

#endif /* __EEPROM_CONFIG_H__ */
