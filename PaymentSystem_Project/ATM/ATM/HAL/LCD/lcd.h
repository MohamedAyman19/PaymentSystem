 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Monica Franics
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include   "..\..\compiler.h"
#include   "..\..\Delay.h"


#include   "..\..\common_macros.h"
#include   "..\..\MCAL\DIO\DIO.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

//#undef UPPER_PORT_PINS /* Use the lower 4-bits in the data port */

/* LCD HW Pins */
/*******/
#define RS Pin5
#define RW Pin6
#define E  Pin7
/*********/
#define LCD_CTRL_PORT PORTC
#define LCD_CTRL_PORT_DIR DDRC
#define LCD_DATA_PORT PORTD
#define LCD_DATA_PORT_DIR DDRD

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80 

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8_t command);
void LCD_displayCharacter(uint8_t data);
void LCD_displayString(const char *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const char *Str);
void LCD_goToRowColumn(uint8_t row,uint8_t col);
//void LCD_intgerToString(int data);
void LCD_voidWriteNumber(uint32_t num);

#endif /* LCD_H_ */
