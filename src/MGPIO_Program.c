/*
 * mGPIO_Program.c
 *
 *  Created on: Jan 22, 2023
 *      Author: Abanoub
 */
#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"
#include "../include/MGPIO_Interface.h"
#include "../include/MGPIO_Private.h"

void MGPIO_voidSetPinMode(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, u8 Copy_u8PinMode)
{
	switch (Copy_uddPortNum)
	{
		case MGPIO_PORTA :
			Clr_BITS(MGPIOA->MODER,(3U<<Copy_uddPinNum*2U));
			MGPIOA->MODER |= (u32)((Copy_u8PinMode << Copy_uddPinNum*2U)); break;

		case MGPIO_PORTB :
			Clr_BITS(MGPIOB->MODER,(3U<<Copy_uddPinNum*2U));
			MGPIOB->MODER |= (u32)((Copy_u8PinMode << Copy_uddPinNum*2U)); break;

		case MGPIO_PORTC :
			Clr_BITS(MGPIOC->MODER,(3U<<Copy_uddPinNum*2U));
			MGPIOC->MODER |= (u32)((Copy_u8PinMode << Copy_uddPinNum*2U)); break;
	}
}
void MGPIO_voidSetOutputType(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, OutputType_t Copy_uddPinOutputType)
{
	switch(Copy_uddPortNum)
		   {
		   case MGPIO_PORTA :
			   	  CLR_BIT(MGPIOA->OTYPER, Copy_uddPortNum);
			      MGPIOA->OTYPER |= (u32)((Copy_uddPinOutputType << Copy_uddPinNum )) ; break ;
		   case MGPIO_PORTB :
			   	  CLR_BIT(MGPIOB->OTYPER, Copy_uddPortNum);
		   	      MGPIOB->OTYPER |= (u32)((Copy_uddPinOutputType << Copy_uddPinNum )) ; break ;
		   case MGPIO_PORTC :
			   	  CLR_BIT(MGPIOC->OTYPER, Copy_uddPortNum);
		   	      MGPIOC->OTYPER |= (u32)(( Copy_uddPinOutputType<< Copy_uddPinNum )) ; break ;
		   default :  /*Do Nothing */                                                  break ;
		   }
}
void MGPIO_voidOutputPinSpeed(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, SPEED_t Copy_uddPinOutputSpeed)
{
	switch(Copy_uddPortNum)
		   {
		   case MGPIO_PORTA :
			   Clr_BITS(MGPIOA->OSPEEDR,(3U<<Copy_uddPinNum * 2U) ) ;
			      MGPIOA->OSPEEDR |= (u32)((Copy_uddPinOutputSpeed << Copy_uddPinNum * 2U )) ; break ;
		   case MGPIO_PORTB :
			   Clr_BITS(MGPIOB->OSPEEDR,(3U<<Copy_uddPinNum * 2U) ) ;
		   	      MGPIOB->OSPEEDR |= (u32)((Copy_uddPinOutputSpeed << Copy_uddPinNum * 2U )) ; break ;
		   case MGPIO_PORTC :
			   Clr_BITS(MGPIOC->OSPEEDR,(3U<<Copy_uddPinNum * 2U) ) ;
		   	      MGPIOC->OSPEEDR |= (u32)((Copy_uddPinOutputSpeed << Copy_uddPinNum * 2U )) ; break ;
		   default :  /*Do Nothing */                                                 break ;
		   }
}
void MGPIO_voidSetPinPullType(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, u8 Copy_u8PullMode)
{
	switch(Copy_uddPortNum)
		   {
		   case MGPIO_PORTA :
			   Clr_BITS(MGPIOA->PUPDR,(3U<<Copy_uddPortNum * 2U) ) ;
			      MGPIOA->PUPDR |= (u32)((Copy_u8PullMode << Copy_uddPinNum * 2U )) ; break ;
		   case MGPIO_PORTB :
			   Clr_BITS(MGPIOB->PUPDR,(3U<<Copy_uddPortNum * 2U) ) ;
		   	      MGPIOB->PUPDR |= (u32)((Copy_u8PullMode << Copy_uddPinNum * 2U )) ; break ;
		   case MGPIO_PORTC :
			   Clr_BITS(MGPIOC->PUPDR,(3U<<Copy_uddPortNum * 2U) ) ;
		   	      MGPIOC->PUPDR |= (u32)((Copy_u8PullMode << Copy_uddPinNum * 2U )) ; break ;
		   default :  /*Do Nothing */                                                 break ;
		   }
}
void MGPIO_voidSetPinValue(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, u8 Copy_u8PinValue)
{
	switch(Copy_uddPortNum)
		   {
		   case MGPIO_PORTA :
			   	  CLR_BIT(MGPIOA->ODR, Copy_uddPinNum);
			      MGPIOA->ODR |= (u32)((Copy_u8PinValue << Copy_uddPinNum )) ; break ;

		   case MGPIO_PORTB :
			   	  CLR_BIT(MGPIOB->ODR, Copy_uddPinNum);
		   	      MGPIOB->ODR |= (u32)((Copy_u8PinValue << Copy_uddPinNum )) ; break ;


		   case MGPIO_PORTC :
			   	  CLR_BIT(MGPIOC->ODR, Copy_uddPinNum);
		   	      MGPIOC->ODR |= (u32)((Copy_u8PinValue << Copy_uddPinNum )) ; break ;

		   default :  /*Do Nothing */                                                  break ;
		   }
}

void MGPIO_voidGetPinValue(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, u8 *Copy_pu8PinValue)
{
	switch(Copy_uddPortNum)
		   {
		   case MGPIO_PORTA :
			      *Copy_pu8PinValue = GET_BIT(MGPIOA->IDR, Copy_uddPinNum) ; break ;
		   case MGPIO_PORTB :
			      *Copy_pu8PinValue = GET_BIT(MGPIOB->IDR, Copy_uddPinNum) ; break ;
		   case MGPIO_PORTC :
			      *Copy_pu8PinValue = GET_BIT(MGPIOC->IDR, Copy_uddPinNum) ; break ;
		   default :  /*Do Nothing */                                                  break ;
		   }
}

void MGPIO_voidSetPortValue(MPORT_t Copy_uddPortNum, u8 Copy_u32PortValue)
{
	switch(Copy_uddPortNum)
		   {
		   case MGPIO_PORTA :

			      MGPIOA->ODR = Copy_u32PortValue ; break ;

		   case MGPIO_PORTB :

		   	      MGPIOB->ODR = Copy_u32PortValue ; break ;


		   case MGPIO_PORTC :

		   	      MGPIOC->ODR = Copy_u32PortValue ; break ;

		   default :  /*Do Nothing */                                                  break ;
		   }
}

