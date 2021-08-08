/********************************************/
/* Author  : Monica Francis		    		*/
/* Date    : 28/7/2021				    	*/
/* Version : V01						    */
/********************************************/

/*FILE GUARD */
#ifndef   __ADC_REGISTER_H__ 
#define   __ADC_REGISTER_H__

/*ADC Registers*/
#define	  ADC       *((volatile uint16_t *)0x24)
#define   ADMUX     *((volatile uint8_t *)0x27)
#define   ADCSRA    *((volatile uint8_t *)0x26)
#define   ADCH      *((volatile uint8_t *)0x25)
#define   ADCL      *((volatile uint8_t *)0x24)
#define   SFIOR     *((volatile uint8_t *)0x50)

#define ADEN    (uint8_t) 7
#define ADSC    (uint8_t) 6
#define ADATE   (uint8_t) 5
#define ADIF    (uint8_t) 4
#define ADIE    (uint8_t) 3
#define ADPS2   (uint8_t) 2
#define ADPS1   (uint8_t) 1
#define ADPS0   (uint8_t) 0

#define REFS1   (uint8_t) 7
#define REFS0   (uint8_t) 6
#define ADLAR   (uint8_t) 5
#define MUX4    (uint8_t) 4
#define MUX3    (uint8_t) 3
#define MUX2    (uint8_t) 2
#define MUX1    (uint8_t) 1
#define MUX0    (uint8_t) 0



/*End of the File Guard*/
#endif
