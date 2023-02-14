///*
// * LCD_Program.c
// *
// *  Created on: Jan 28, 2023
// *      Author: Abanoub
// */
#include "../include/LSTD_TYPES.h"
#include "../include/LERROR_STATES.h"
#include "../include/LBIT_MATH.h"
#include "../include/MGPIO_Interface.h"
#include "../include/MSTK_Interface.h"
#include "../include/LCD_Interface.h"
#include "../include/LCD_Config.h"


void HLCD_voidInit(void)
{

	MSTK_voidDelayMs(200) ;
	HLCD_voidSendCommand(FUNCTION_SET_8BIT);
	MSTK_voidDelayMs(20) ;
	HLCD_voidSendCommand(LCD_DISPLAY);
	MSTK_voidDelayMs(20) ;
	HLCD_voidSendCommand(LCD_CLEAR);
	MSTK_voidDelayMs(20) ;
	HLCD_voidSendCommand(LCD_ENTRYMODE);

}
void HLCD_voidSendCommand(u8 Copy_u8Cmd)
{
	//RS LOW
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,MGPIO_PIN_LOW);
	//Command
	MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN0,(GET_BIT(Copy_u8Cmd,0)));
	MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN1,(GET_BIT(Copy_u8Cmd,1)));
	MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN2,(GET_BIT(Copy_u8Cmd,2)));
	MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN3,(GET_BIT(Copy_u8Cmd,3)));
	MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN4,(GET_BIT(Copy_u8Cmd,4)));
	MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN5,(GET_BIT(Copy_u8Cmd,5)));
	MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN6,(GET_BIT(Copy_u8Cmd,6)));
	MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN7,(GET_BIT(Copy_u8Cmd,7)));

	//Enable
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,MGPIO_PIN_HIGH);
	MSTK_voidDelayMs(4) ;
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,MGPIO_PIN_LOW);


}
void HLCD_voidSendChar(u8 Copy_u8Char)
{

	//RS High
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,MGPIO_PIN_HIGH);
	//Command
		MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN0,(GET_BIT(Copy_u8Char,0)));
		MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN1,(GET_BIT(Copy_u8Char,1)));
		MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN2,(GET_BIT(Copy_u8Char,2)));
		MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN3,(GET_BIT(Copy_u8Char,3)));
		MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN4,(GET_BIT(Copy_u8Char,4)));
		MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN5,(GET_BIT(Copy_u8Char,5)));
		MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN6,(GET_BIT(Copy_u8Char,6)));
		MGPIO_voidSetPinValue(LCD_DATA_PORT,PIN7,(GET_BIT(Copy_u8Char,7)));
	//Enable
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,MGPIO_PIN_HIGH);
	MSTK_voidDelayMs(4) ;
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,MGPIO_PIN_LOW);


}

void HLCD_voidGotoxy(u8 X,u8 Y)
{
	if(Y==0)
	{
	HLCD_voidSendCommand(LCD_SETCURSER|X) ;
	}
	else
	{
		HLCD_voidSendCommand((LCD_SETCURSER|X) | (0x40)) ;
	}

}

void HLCD_voidSendString(u8 *Copy_u8ptrString)
{

	while(*Copy_u8ptrString!='\0')
	{
		HLCD_voidSendChar(*Copy_u8ptrString);
		Copy_u8ptrString++;

	}
}

void LCD_Send_Num(u32 num)
{
	int txt[10] = {0};					// Array holds the number in digits
	int i = 0;						// Iterator
	if(num == 0)
	{
		HLCD_voidSendChar('0');
		return;
	}
	for(i = 0; num != 0; i++)
	{
		txt[i] = num%10 +48;				// Get the ASCII code of the rightmost digit
		num = num/ 10;					// Remove the rightmost digit
	}
	i--;
	while(i >= 0 )
	{
		HLCD_voidSendChar(txt[i]);				// Display the digits in reverse order
		i--;
	}
}
void LCD_Send_Float(f32 num)
{
	f32 num2ndPart;
	s32 num1stPart = (u32) num;
	LCD_Send_Num(num1stPart);

	num2ndPart = (f32) num-num1stPart;
	if (num < 0) {
		num2ndPart = (f32) (-1) * (num2ndPart);
	}
	if(((f32)num-num1stPart)>0)
	{
		HLCD_voidSendChar('.');
			u8 zero_flag=0,temp;
			for (u8 i = 1; i <= 4; i++) {
				num2ndPart = num2ndPart * 10;
				 temp = (u8) num2ndPart;
				if((temp==0)&&zero_flag&&i<=3)
				{
					HLCD_voidSendChar('0');
					break;
				}
				else if(zero_flag&&(temp>0))
				{
					if(temp>=4)
						HLCD_voidSendChar('1');
					else
						HLCD_voidSendChar('0');
					break;
				}
				else if(temp==0)
				{
					zero_flag=1;
				}
				else
				{
					HLCD_voidSendChar(temp + '0');
				}
				num2ndPart = (f32) (num2ndPart - temp);
			}
	}
	}

