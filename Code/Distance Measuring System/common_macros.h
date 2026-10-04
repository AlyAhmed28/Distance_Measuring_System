/*
 * [FILE NAME]		:		common_macros.h
 *
 * [AUTHOR]			:		Aly Ahmed
 *
 * [FILE CREATED]	:		18/01/2024
 *
 * [DESCRIPTION]	:		This header File that has the common macros used for AVR
 *
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT)		(REG |= (1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT)		(REG &= (~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT)		(REG ^= (1<<BIT))

/* Rotate Right the register value with a specific number of rotates */
#define ROR(REG,num)			( REG = (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num)			( REG = (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit in a register is set and return true if yes */
#define BIT_IS_SET(REG,BIT)		( REG & (1<<BIT) )

/* Check if a specific bit in a register is clear and return true if yes */
#define BIT_IS_CLEAR(REG,BIT)	( !(REG & (1<<BIT)) )



#endif /* COMMON_MACROS_H_ */
