/*
 * utils.h
 *
 * Created: 7/20/2021 2:37:53 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __UTILS_H__
#define __UTILS_H__

/*- INCLUDES -----------------------------------------------*/
#include "compiler.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* dummy delay for nearly 50ms */
void dummy_delay(void);

/* compares two strings if identical */
uint8_t StringCompare(uint8_t * str1, uint8_t * str2);

/* get string size */
uint8_t StringLength(uint8_t * string);

#endif /* __UTILS_H__ */
