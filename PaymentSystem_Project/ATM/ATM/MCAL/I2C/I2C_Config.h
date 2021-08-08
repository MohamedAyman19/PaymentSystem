/*
 * I2C_Config.h
 *
 * Created: 7/16/2021 9:32:31 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

/*- INCLUDES -----------------------------------------------*/
#include "..\..\compiler.h"

/*- MACROS -------------------------------------------------*/
#define I2C_INTERRUPT_EN            (uint8_t)(0X01)
#define I2C_ACK_EN                  (uint8_t)(0X40)
#define I2C_EN                      (uint8_t)(0X04)

#define I2C_INTERRUPT_FLAG          (uint8_t)(0X80)
#define I2C_START_BIT               (uint8_t)(0X20)
#define I2C_STOP_BIT                (uint8_t)(0X10)
#define I2C_WRITE_COLLISION_FLAG    (uint8_t)(0X08)
#define I2C_STATUS_BITS             (uint8_t)(0xF8)

#define I2C_PRESCALAR_1             (uint8_t)(0X00)
#define I2C_PRESCALAR_4             (uint8_t)(0X01)
#define I2C_PRESCALAR_16            (uint8_t)(0X02)
#define I2C_PRESCALAR_64            (uint8_t)(0X03)

#define I2C_8_MHZ_115200_RATE_1_PRESCALAR       (uint8_t)(0X07)      

#define I2C_NUMBERS                 (uint8_t)(1)

#define I2C_CH_0                    (uint8_t)(0)
#define I2C_CH_0_PRESCALER          I2C_PRESCALAR_64
#define I2C_CH_0_CONTROL_MASK       (I2C_EN)
#define I2C_CH_0_BIT_RATE           I2C_8_MHZ_115200_RATE_1_PRESCALAR
           
#define I2C_STATUS_START            (uint8_t)(0x08)
#define I2C_STATUS_T_ACK_ADDR       (uint8_t)(0x18)
#define I2C_STATUS_T_ACK_DATA       (uint8_t)(0x28)
#define I2C_STATUS_R_ACK_ADDR       (uint8_t)(0x60)
#define I2C_STATUS_R_ACK_DATA       (uint8_t)(0x80)

#endif /* __I2C_CONFIG_H__ */
