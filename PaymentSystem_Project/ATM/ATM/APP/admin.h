/*
 * admin.h
 *
 * Created: 7/15/2021 1:05:48 AM
 *  Author: Marco
 */ 


#ifndef ATM_H_
#define ATM_H_

/******************************************************************************
*                              Includes													*
*******************************************************************************/
#include "admin_Config.h"

/******************************************************************************
*                               FUNCTION DECLARATIONS                         *
*******************************************************************************/
void ADMIN_Mode(void);
void ADMIN_Authenticate(void);
uint8_t ADMIN_Interface(void);
void ADMIN_SetAccount(void);
void ADMIN_GetAccount(void);
void ADMIN_SetMaxBalance(void);
void ADMIN_GetMaxBalance(void);


#endif /* ATM_H_ */