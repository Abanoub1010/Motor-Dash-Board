/*
 * MSTK_Program.c
 *
 *  Created on: Jan 24, 2023
 *      Author: Ahmed Khaled Hammad
 */

/***************************************************************************************/
/*                            StandarAd Types LIB                                       */
/***************************************************************************************/

#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"


/***************************************************************************************/
/*                                    Lower Layer                                      */
/***************************************************************************************/



/***************************************************************************************/
/*                                    Own Header                                       */
/***************************************************************************************/

#include "../include/MSTK_Private.h"
#include "../include/MSTK_Interface.h"
#include "../include/MGPIO_Interface.h"

/***************************************************************************************/
/*                                    Function Implementation                          */
/***************************************************************************************/

static void (*MSTK_CallBack)(void)  ;

// calling by Hardware if interrupt happens
void SysTick_Handler(void)
{
	// Execute CallBack Function
	MSTK_CallBack() ;
}

void MSTK_voidInit(void)
{
	//TODO
	/* [Enable Systick Interrupt - clock = AHB/8 - Stop Systick]*/
//	SET_BIT(STK_CTRL,TIKINT_STK_CTRL);

	CLR_BIT(STK_CTRL,CLKSOURCE_STK_CTRL);

	CLR_BIT(STK_CTRL,ENABLE_STK_CTRL);

}
void MSTK_voidStart(u32 Copy_u32PreloadVal)
{
	//if F_CPU -> HSI = 16MHz , AHB = 16 MHz , F_Timer = AHB/8 = 2 MHz
	// 0.5 us for each count

	//Step 1: Load Value
	STK_LOAD=(Copy_u32PreloadVal);

	//Step 2: Clear Val Reg
	STK_VAL=0;

	//Step 3: Enable Systick
	SET_BIT(STK_CTRL,ENABLE_STK_CTRL) ;
}
u8   MSTK_u8ReadCountFlag(void)
{
	//TODO
	//Step 1 : Get Count Flag
	return GET_BIT(STK_CTRL,COUNTFLAG_STK_CTRL);
}
void MSTK_voidSetIntStatus(u8 Copy_uddtIntStatus)
{
	//TODO
	//Step 1 : Clear Bit of Interrupt
	//Step 2 : Set the Bit of interrupt with the input
	if (Copy_uddtIntStatus == MSTK_INT_DISABLE)
			{
				CLR_BIT(STK_CTRL,ENABLE_STK_CTRL);
			}
		else if (Copy_uddtIntStatus == MSTK_INT_ENABLE)
			{
				SET_BIT(STK_CTRL,ENABLE_STK_CTRL);
			}


}

void MSTK_voidDelayMs(u32 Copy_u32Time)
{
	//TODO
	//Step 1 : Init Systick
	MSTK_voidInit() ;

	//Step 2 : Disable INT
	CLR_BIT(STK_CTRL,TIKINT_STK_CTRL); ;

	//Step 3 : Start Systick( Copy_u32Time )
    MSTK_voidStart(Copy_u32Time*2000) ;
	//Step 4 : Wait Flag Polling */

	while(MSTK_u8ReadCountFlag() == 0) ;

}

//void MSTK_voidDelayUs(u32 Copy_u32Time)
//{
////TODO
//	//Step 1 : Init Systick
//
//	//Step 2 : Disable INT
//
//	//Step 3 : Start Systick( Copy_u32Time)
//
//	//Step 4 : Wait Flag Polling */
//	while(MSTK_u8ReadCountFlag() == 0) ;
//}
void MSTK_voidSetCallBack(void (*PFunc)(void))
{
	// assign the function passed  to Global pointer
	MSTK_CallBack = PFunc ;
}
