/*
 * DC_Motor.c
 *
 * Created: 28-Jul-21 11:21:38 PM
 *  Author: ayman
 */ 
#include "..\..\common_macros.h"
#include "..\..\compiler.h"
#include "..\..\MCAL\DIO\DIO.h"
#include "DC_MotorConfig.h"
#include "DC_Motor.h"
void DC_MotorInit()
{
	DIO_setPinDirection(DC_MotorPort,DCMotorPin,OUTPUT);
	
}
void DC_MotorStart()
{
	DIO_writePin(DC_MotorPort,DCMotorPin,HIGH);
}
void DC_MotorStop()
{
	DIO_writePin(DC_MotorPort,DCMotorPin,LOW);
}