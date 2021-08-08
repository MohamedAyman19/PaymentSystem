/*
 * utils.c
 *
 * Created: 7/20/2021 2:38:04 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "utils.h"
#include "compiler.h"

/*- LOCAL MACROS
------------------------------------------*/
#define TRUE                  (uint8_t)(1)
#define FALSE                 (uint8_t)(0)

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function is a dummy delay.
*/
void dummy_delay(void)
{
   for(volatile uint16_t i=0; i<100; i++)
   {
      for(volatile uint8_t j=0; j<32; j++)
      {
         for(volatile uint8_t k=0; k<2; k++)
         {
            
         }
      }
   }
}

/**
* @brief: This function compares if two strings are identical.
*
* @param [in]  str1   -  pointer to the first string.
* @param [in]  str2   -  pointer to the second string.
*
* @return function error state.
*/
uint8_t StringCompare(uint8_t * str1, uint8_t * str2)
{
   uint8_t u8_counter = 0;
   uint8_t u8_isEqual = TRUE;
   
   while(str1[u8_counter] != END_OF_STRING && str1[u8_counter] != NEW_LINE)
   {
      if(str1[u8_counter] != str2[u8_counter])
      {
         u8_isEqual = FALSE;
         u8_counter++;
         break;
      }
      u8_counter++;
   }
   if( str2[u8_counter] != END_OF_STRING )
   {
      u8_isEqual = FALSE;
   }
   return u8_isEqual;
}

/**
* @brief: This function gets string size.
*
* @param [in]  string   -  pointer to the string.
*
* @return function error state.
*/
uint8_t StringLength(uint8_t * string)
{
   uint8_t u8_counter = 0;
  
   while(string[u8_counter] != END_OF_STRING && string[u8_counter] != NEW_LINE)
   {
      u8_counter++;
   }
   
   return u8_counter;
}
