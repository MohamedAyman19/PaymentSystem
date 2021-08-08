/*
 * compiler.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: VIP B
 */

#ifndef COMPILER_H_
#define COMPILER_H_

typedef signed char           sint8_t;
typedef unsigned char         uint8_t;
typedef signed short          sint16_t;
typedef unsigned short        uint16_t;
typedef signed long           sint32_t;
typedef unsigned long         uint32_t;
typedef signed long long      sint64_t;
typedef unsigned long long    uint64_t;
typedef float                 float32_t;
typedef double                float64_t;

typedef uint8_t * ptr_uint8_t;

typedef void(*Ptr_VoidFuncVoid_t)(void);

/*- MACROS -------------------------------------------------*/
#define NULL_PTR        ((void*)(0))

#define END_OF_STRING   (uint8_t)('\0')
#define NULL_TERMINATOR   (uint8_t)('\0')
#define NEW_LINE        (uint8_t)('\r')
#define BACKSPACE       (uint8_t)('\b')
#define EMPTY_STRING    (uint8_t)(0x00)

#endif /* COMPILER_H_ */
