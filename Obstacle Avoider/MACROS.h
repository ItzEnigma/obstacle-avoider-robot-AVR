/*
 * MACROS.h
 *
 * Created: 3/25/2022 3:21:30 PM
 *  Author: hosam
 */ 


#ifndef MACROS_H_
#define MACROS_H_

// CPU Clock Speed
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

// Port C ... is 7 pins only (PC6 : PC0)

				// ----- GPIO Registers ----- //
#define SetBit(REG,BIT) (REG|= (1<<BIT))
#define ResetBit(REG,BIT) (REG&= ~(1<<BIT))
#define ToggleBit(REG,BIT) (REG^= (1<<BIT))
#define isSet(REG,BIT) (REG & (1<<BIT))

				// ----- GPIO Direction Manipulation ----- //
#define setPort_Dir(REG,DIR) (REG = DIR)
#define setBit_Dir(REG,BIT,DIR) (REG|= DIR<<BIT)
#define Enable_Pullup(REG,BIT) (REG|= 1<<BIT)

				// ----- Data Types ----- //
typedef volatile unsigned char u08;
typedef volatile signed char s08;
typedef volatile unsigned int u16;
typedef volatile signed int s16;
typedef volatile float f32;
typedef volatile long int s32;
typedef volatile unsigned long int u32;
typedef volatile unsigned long long int u64;

#endif /* MACROS_H_ */