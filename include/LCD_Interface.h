/*
 * LCD_Interface.h
 *
 *  Created on: Jan 28, 2023
 *      Author: Abanoub
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"

#define FUNCTION_SET_8BIT  			0x38  //8 it mode
#define LCD_DISPLAY         		0x0C
#define LCD_CLEAR					0x01
#define LCD_ENTRYMODE				0x06
#define LCD_SETCURSER				0x80




void HLCD_voidInit(void);
void HLCD_voidSendCommand(u8 Copy_u8Cmd);
void HLCD_voidSendChar(u8 Copy_u8Char);
void HLCD_voidGotoxy(u8 X,u8 Y);
void HLCD_voidSendString(u8 *Copy_u8ptrString);
void LCD_Send_Float(f32 num);
void LCD_Send_Num(u32 num);



#endif /* LCD_INTERFACE_H_ */
