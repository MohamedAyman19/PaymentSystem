/*
* admin.c
*
* Created: 7/15/2021 1:05:37 AM
*  Author: Marco
*/

#ifndef __ADMIN_CONFIG_H__
#define __ADMIN_CONFIG_H__

/******************************************************************************
*                              Includes													*
*******************************************************************************/
#include <math.h>
#include "../MCAL/I2C/I2C.h"
#include "../HAL/EEPROM/EEPROM.h"
#include "../MCAL/DIO/dio.h"
#include "../MCAL/UART/UART.h"

/******************************************************************************
*                              CONSTANTS													*
*******************************************************************************/
#define I2C_DDR									PORTC_DIR
#define SCL											PIN_0
#define SDA											PIN_1

#define FALSE									(uint8_t) 0
#define TRUE									(uint8_t) 1

#define EEPROM_CH									EEPROM_CH_0

#define AVALIABLE_ACCOUNTS_NULL				(uint8_t) ('N')

#define PASS_BLOCK								MEMORY_BLOCK_1
#define MAX_ACCOUNT_BLOCK						MEMORY_BLOCK_2
#define AVALIABLE_ACCOUNTS_BLOCK				MEMORY_BLOCK_3
#define ACCOUNTS_BLOCK							MEMORY_BLOCK_4

#define PASS_ADDR									(uint8_t) (0)
#define MAX_ACCOUNT_ADDR						(uint8_t) (0)
#define AVALIABLE_ACCOUNTS_ADDR				(uint8_t) (0)
#define ACCOUNTS_ADDR							(uint8_t) (0)

#define PASS_BYTES_NO							(uint8_t) (4)
#define PASS_BYTES_GUARD_NO					(uint32_t) (PASS_BYTES_NO + 1)
#define PAN_BYTES_NO							   (uint8_t) (9)
#define PAN_BYTES_GUARD_NO					   (uint32_t) (PAN_BYTES_NO + 1)
#define SPACE_BYTES_NO							(uint8_t) (1)
#define MAX_ACCOUNT_BYTES_NO					(uint8_t) (4)
#define TOTAL_FRAME_NO							(uint8_t) (PAN_BYTES_NO + MAX_ACCOUNT_BYTES_NO + SPACE_BYTES_NO)

#define USER_PASS_BYTES_NO						(uint8_t) (10)
#define MAX_PASS_BYTES_NO						(uint8_t) (16)
#define FLOATING_POINT							(uint8_t) (2)

#define MAX_BALANCE_NO							(uint32_t) (9999.99)
#define MAX_ACCOUNT_NO							(uint8_t) ('8')

#define OPTION_SET_CUSTOMER_DATA				(uint8_t) ('1')
#define OPTION_GET_CUSTOMER_DATA				(uint8_t) ('2')
#define OPTION_SET_MAX_ACCOUNT				(uint8_t) ('3')
#define OPTION_GET_MAX_ACCOUNT				(uint8_t) ('4')
#define OPTION_EXIT								(uint8_t) ('5')

#define STRING_INVALID_PIN						(uint8_t *) ("[INFO] INVALID PIN Try Again...")
#define STRING_INVALID_PAN						(uint8_t *) ("[INFO] INVALID PAN MUST BE 9 CHARACTERS Try Again...")
#define STRING_PAN_EXISTS						(uint8_t *) ("[INFO] INVALID PAN ALREADY EXISTS...")
#define STRING_INVALID_CHOICE					(uint8_t *) ("[INFO] INVALID CHOICE Try Again...")
#define STRING_INVALID_MAX_ACCOUNT			(uint8_t *) ("[INFO] INVALID BALANCE...")
#define STRING_MEMORY_EMPTY					(uint8_t *) ("[INFO] MEMORY EMPTY")
#define STRING_MEMORY_FULL						(uint8_t *) ("[INFO] MEMORY FULL")
#define STRING_WELCOME_START					(uint8_t *) ("********Welcome to ATM Service**************")
#define STRING_WELCOME_END						(uint8_t *) ("********************************************")

#define STRING_MENU_SET_CUSTOMER_DATA		(uint8_t *) ("1. Set Customer Data")
#define STRING_MENU_GET_CUSTOMER_DATA		(uint8_t *) ("2. Get Customer Data")
#define STRING_MENU_SET_MAX_ACCOUNT			(uint8_t *) ("3. Set Maximum Balance Account")
#define STRING_MENU_GET_MAX_ACCOUNT			(uint8_t *) ("4. Get Maximum Balance Account")
#define STRING_MENU_EXIT						(uint8_t *) ("5. Quit")
#define STRING_MENU_CHOICE  					(uint8_t *) ("Enter your choice: ")

#define STRING_ENTER_PIN						(uint8_t *) ("ENTER YOUR SECRET PIN: ")
#define STRING_ENTER_PAN						(uint8_t *) ("ENTER YOUR SECRET PAN: ")
#define STRING_ENTER_ACCOUNT					(uint8_t *) ("ENTER YOUR AMOUNT BALANCE: ")

#define STRING_ACCOUNTS_AVALIABLE			(uint8_t *) ("ACCOUNTS AVALIABLE: ")
#define STRING_MAX_ACCOUNT						(uint8_t *) ("ENTER MAX BALANCE NUMBER: ")
#define STRING_PAN								(uint8_t *) ("PAN: ")
#define STRING_ACCOUNT							(uint8_t *) ("BALANCE: ")

#define STRING_EXIT								(uint8_t *) ("THANK U FOR USING ATM MACHINE")

#endif /* __ADMIN_CONFIG_H__ */