#include "compiler.h"

#define Z 9200
#define M 5300

void _delay_ms(uint32_t DelayValue)
{
	uint32_t i = 0;
	uint32_t count = (DelayValue*1000000 - Z)/(M+125);
	for(;i < count ; i++)
		asm("NOP");
}
