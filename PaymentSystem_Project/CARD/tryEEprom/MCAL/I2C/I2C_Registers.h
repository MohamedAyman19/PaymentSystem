/*
 * I2C_Registers.h
 *
 * Created: 7/16/2021 9:32:49 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __I2C_REGISTERS_H__
#define __I2C_REGISTERS_H__

#define TEST 0

#if !TEST
/*- I2C REGISTERS-----------------------------------------*/
#define  I2C_DATA_R           (*((volatile uint8_t *) (0x23)))
#define  I2C_SLAVE_ADDR_R      (*((volatile uint8_t *) (0x22)))
#define  I2C_STATUS_R         (*((volatile uint8_t *) (0x21)))
#define  I2C_BIT_RATE_R       (*((volatile uint8_t *) (0x20)))
#define  I2C_CONTROL_R        (*((volatile uint8_t *) (0x56)))
#else
/*- I2C REGISTERS-----------------------------------------*/
extern volatile uint8_t  I2C_DATA_R;
extern volatile uint8_t  I2C_SLAVE_ADDR_R;
extern volatile uint8_t  I2C_STATUS_R;
extern volatile uint8_t  I2C_BIT_RATE_R;
extern volatile uint8_t  I2C_CONTROL_R;
#endif

#endif /* __I2C_REGISTERS_H__ */