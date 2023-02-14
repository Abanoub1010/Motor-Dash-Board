/*
 * MSTK_Private.h
 *
 *  Created on: Jan 24, 2023
 *      Author: Abanoub
 */

#ifndef MSTK_PRIVATE_H_
#define MSTK_PRIVATE_H_


/*Register definition*/

#define		 	STK_CTRL		(*((volatile u32*)(0xE000E010)))
#define 		STK_LOAD		(*((volatile u32*)(0xE000E014)))
#define 		STK_VAL			(*((volatile u32*)(0xE000E018)))
#define 		STK_CALIB		(*((volatile u32*)(0xE000E01C)))


#define		 	ENABLE_STK_CTRL			0
#define		 	TIKINT_STK_CTRL			1
#define		 	CLKSOURCE_STK_CTRL		2
#define		 	COUNTFLAG_STK_CTRL		16


#endif /* MSTK_PRIVATE_H_ */
