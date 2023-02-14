/***************************************************************************************/
/* Author               : Ahmed Hammad                                                 */
/* Version              : V0.0.0                                                       */
/* Date                 : 22 - 1 -2023                                                 */
/* Description          : MGPIO_Interface.h -> Function Prototypes                     */
/* Module Features      :                                                              */
/*        01- MGPIO_voidSetPinMode                                                      */
/*        02- MGPIO_voidSetOutputType                                                   */
/*        03- MGPIO_voidSetOutputPinSpeed                                               */
/*        04- MGPIO_voidSetPinPullType                                                  */
/*        05- MGPIO_voidSetPinValue                                                     */
/*        06- MGPIO_voidGetPinValue	  												   */
/* Future Update:																	   */
/* 		  07- MGPIO_voidSetPinLock													   */
/* 		  08- MGPIO_voidSetResetPin													   */
/* 		  09- MGPIO_voidSetPinAlternativeFunc                                           */
/***************************************************************************************/

/***************************************************************************************/
/*          * What i sell to customer                                                  */
/*                        * The Architecture Give The API                              */
/*                                           - The Name Of Function                    */
/*                                           - What is The input                       */
/*                                           - What is The Output                      */
/*                                           - Macro                                   */
/***************************************************************************************/


/***************************************************************************************/
/*                            Guard of file will call on time in c file                */
/***************************************************************************************/

#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

/***************************************************************************************/
/*                            Standard Types LIB                                       */
/***************************************************************************************/

#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"

/***************************************************************************************/
/*                                   GPIO_Name                                         */
/***************************************************************************************/

typedef enum
{
	MGPIO_PORTA,
	MGPIO_PORTB,
	MGPIO_PORTC
}MPORT_t;


/***************************************************************************************/
/*                                   PIN_Name                                          */
/***************************************************************************************/

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PIN_t;

/***************************************************************************************/
/*                                  Speed_Name                                         */
/***************************************************************************************/
typedef enum
{
	MGPIO_SPEED_LOW,
	MGPIO_SPEED_MID,
	MGPIO_SPEED_HIGH,
	MGPIO_SPEED_VHIGH
}SPEED_t;


/***************************************************************************************/
/*                                  PIN_MODE                                         */
/***************************************************************************************/

#define		MGPIO_PIN_INPUT 	0b00
#define		MGPIO_PIN_OUTPUT 	0b01
#define		MGPIO_PIN_ALTF		0b10
#define		MGPIO_PIN_ANALOG	0b11

/***************************************************************************************/
/*                                OUTPUT_MODE                                         */
/***************************************************************************************/
typedef enum
{
	MGPIO_PUSH_PULL,
	MGPIO_OPEN_DRAIN
}OutputType_t;


/***************************************************************************************/
/*                                PULL_MODE                                         */
/***************************************************************************************/

#define 	MGPIO_PIN_FLOAT			0b00
#define 	MGPIO_PIN_PULL_UP		0b01
#define 	MGPIO_PIN_PULL_DOWN		0b10


/***************************************************************************************/
/*                               Pin_Value                                        */
/***************************************************************************************/

#define 	MGPIO_PIN_HIGH		1
#define 	MGPIO_PIN_LOW		0

/***************************************************************************************/
/*									Function_prototypes			    				   */
/***************************************************************************************/

void MGPIO_voidSetPinMode(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, u8 Copy_u8PinMode);

void MGPIO_voidSetOutputType(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, OutputType_t Copy_uddPinOutputType);

void MGPIO_voidOutputPinSpeed(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, SPEED_t Copy_uddPinOutputSpeed);

void MGPIO_voidSetPinPullType(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, u8 Copy_u8PullMode);

void MGPIO_voidSetPinValue(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, u8 Copy_u8PinValue);

void MGPIO_voidGetPinValue(MPORT_t Copy_uddPortNum, PIN_t Copy_uddPinNum, u8 *Copy_pu8PinValue);

void MGPIO_voidSetPortValue(MPORT_t Copy_uddPortNum,u8 Copy_u32PortValue);

















#endif /* MGPIO_INTERFACE_H_ */
