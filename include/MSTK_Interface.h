/*
 * MSTK_Interface.h
 *
 *  Created on: Jan 24, 2023
 *      Author:
 */

#ifndef MSTK_INTERFACE_H_
#define MSTK_INTERFACE_H_

#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"


#define	MSTK_INT_DISABLE 	0
#define	MSTK_INT_ENABLE		1


void MSTK_voidInit(void) ;
void MSTK_voidStart(u32 Copy_u32PreloadVal) ;
u8   MSTK_u8ReadCountFlag(void) ;
void MSTK_voidSetIntStatus(u8 Copy_uddtIntStatus) ;
void MSTK_voidDelayMs(u32 Copy_u32Time) ;
void MSTK_voidDelayUs(u32 Copy_u32Time) ;
void MSTK_voidSetCallBack(void (*PFunc)(void)) ;

#endif /* MSTK_INTERFACE_H_ */
