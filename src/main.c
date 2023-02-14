/*
 * main.c
 *
 *  Created on: Jan 17, 2023
 *      Author: Ahmed Khaled Hammad
 */

/***************************************************************************************/
/*                            Standard Types LIB                                       */
/***************************************************************************************/

#include "../include/LSTD_TYPES.h"
#include "../include/LERROR_STATES.h"
#include "../include/LBIT_MATH.h"



/***************************************************************************************/
/*                                     MCAL                                            */
/***************************************************************************************/
#include "../include/MRCC_Interface.h"
#include "../include/MGPIO_Interface.h"
#include "../include/MGPIO_Private.h"
#include "../include/MSTK_Interface.h"
/***************************************************************************************/
/*                                     HAL                                             */
/***************************************************************************************/
#include "../include/LCD_Interface.h"
#include "../include/LCD_Config.h"
#include "../include/KPD_Interface.h"
/***************************************************************************************/
/*                                     APP                                             */
/***************************************************************************************/
#define 	CORRECT_PASS 	5
#define 	WRONG_PASS		0
/*Component Selection*/
#define 	BUZZER_MENUE	1
#define 	LED_MENUE		2
#define 	MOTOR_MENUE		3
/*State Selection*/
#define 	ON				1
#define 	OFF				2
#define 	BACK			3


void Set_Passward (void);
void Passward_Check(void);
void Main_Menu(void);
void User_Entery(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Led_On(void);
void Led_Off(void);
void Motor_On(void);
void Motor_Off(void);


u8 Global_PressedKey;

u8 Global_PassNum1;
u8 Global_PassNum2;
u8 Global_PassNum3;
u8 Global_PassNum4;

u8 Global_SetPassCheck=0;

u8 Global_Retry;

u8 Global_ComponentSelection;
u8 Global_StateSelection;

u8 seg [4]=	{0b00111111, 0b00110000,
						0b01011011, 0b01001111};
void main(void)
{

    /*Step 1: System Clock  */
	MRCC_voidInitSystemClock() ;

	/*Step 2: Enable GPIO Peripheral Clock For Port A */
	MRCC_voidEnablePeripheralClock(AHB1,MRCC_PERIPHERIAL_EN_GPIOA) ;
	MRCC_voidEnablePeripheralClock(AHB1,MRCC_PERIPHERIAL_EN_GPIOB) ;
	MRCC_voidEnablePeripheralClock(AHB1,MRCC_PERIPHERIAL_EN_GPIOC) ;

	/*Step 3 : Configure PA0 as output pin*/
	/*Port direction of data*/
	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN0,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN1,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN2,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN3,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN4,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN5,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN6,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN7,MGPIO_PIN_OUTPUT);




	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN8,MGPIO_PIN_OUTPUT); //Buzzer
	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN9,MGPIO_PIN_OUTPUT); //LED


	MGPIO_voidSetPinMode(MGPIO_PORTA,PIN10,MGPIO_PIN_OUTPUT); //Motor
	MGPIO_voidSetOutputType(MGPIO_PORTA,PIN10,MGPIO_OPEN_DRAIN);
	Motor_Off();


	/*RS and E direction*/
	MGPIO_voidSetPinMode(LCD_CONTROL_PORT,LCD_RS_PIN,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(LCD_CONTROL_PORT,LCD_E_PIN,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(LCD_CONTROL_PORT,LCD_RW_PIN,MGPIO_PIN_OUTPUT);

	/*LCD init*/
	HLCD_voidInit();

	/*Keypad*/
	/*Columns*/
	MGPIO_voidSetPinMode(MGPIO_PORTB,PIN0,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTB,PIN1,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTB,PIN2,MGPIO_PIN_OUTPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTB,PIN3,MGPIO_PIN_OUTPUT);

	MGPIO_voidSetPinValue(MGPIO_PORTB,PIN0,MGPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(MGPIO_PORTB,PIN1,MGPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(MGPIO_PORTB,PIN2,MGPIO_PIN_HIGH);
	MGPIO_voidSetPinValue(MGPIO_PORTB,PIN3,MGPIO_PIN_HIGH);

	/*Rows*/
	MGPIO_voidSetPinMode(MGPIO_PORTB,PIN4,MGPIO_PIN_INPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTB,PIN5,MGPIO_PIN_INPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTB,PIN6,MGPIO_PIN_INPUT);
	MGPIO_voidSetPinMode(MGPIO_PORTB,PIN7,MGPIO_PIN_INPUT);
	MGPIO_voidSetPinPullType(MGPIO_PORTB,PIN4,MGPIO_PIN_PULL_UP);
	MGPIO_voidSetPinPullType(MGPIO_PORTB,PIN5,MGPIO_PIN_PULL_UP);
	MGPIO_voidSetPinPullType(MGPIO_PORTB,PIN6,MGPIO_PIN_PULL_UP);
	MGPIO_voidSetPinPullType(MGPIO_PORTB,PIN7,MGPIO_PIN_PULL_UP);

	MSTK_voidDelayMs(10);
	HLCD_voidSendString("Enter Pass:");

	while(1)
	{
		Set_Passward();
		Passward_Check();
		Main_Menu();
		User_Entery();
	}
}

void Set_Passward(void)
{

	while (Global_SetPassCheck < 4 && Global_Retry <4)
	{
		Global_PressedKey= KPD_u8GetPressedKey() ;
	if (Global_PressedKey!=0xFF)
	{
		HLCD_voidSendChar('*');
		if(Global_SetPassCheck==0)
			{
				switch(Global_PressedKey)
					{
						case '0': Global_PassNum1=0; Global_SetPassCheck=1; break;
						case '1': Global_PassNum1=1; Global_SetPassCheck=1; break;
						case '2': Global_PassNum1=2; Global_SetPassCheck=1; break;
						case '3': Global_PassNum1=3; Global_SetPassCheck=1; break;
						case '4': Global_PassNum1=4; Global_SetPassCheck=1; break;
						case '5': Global_PassNum1=5; Global_SetPassCheck=1; break;
						case '6': Global_PassNum1=6; Global_SetPassCheck=1; break;
						case '7': Global_PassNum1=7; Global_SetPassCheck=1; break;
						case '8': Global_PassNum1=8; Global_SetPassCheck=1; break;
						case '9': Global_PassNum1=9; Global_SetPassCheck=1; break;
						default: /*TODO*/ break;
					}
			}
		else if(Global_SetPassCheck==1)
			{
				switch(Global_PressedKey)
					{
						case '0': Global_PassNum2=0; Global_SetPassCheck=2; break;
						case '1': Global_PassNum2=1; Global_SetPassCheck=2; break;
						case '2': Global_PassNum2=2; Global_SetPassCheck=2; break;
						case '3': Global_PassNum2=3; Global_SetPassCheck=2; break;
						case '4': Global_PassNum2=4; Global_SetPassCheck=2; break;
						case '5': Global_PassNum2=5; Global_SetPassCheck=2; break;
						case '6': Global_PassNum2=6; Global_SetPassCheck=2; break;
						case '7': Global_PassNum2=7; Global_SetPassCheck=2; break;
						case '8': Global_PassNum2=8; Global_SetPassCheck=2; break;
						case '9': Global_PassNum2=9; Global_SetPassCheck=2; break;
						default: /*TODO*/ break;
					}
			}
		else if(Global_SetPassCheck==2)
			{
				switch(Global_PressedKey)
					{
						case '0': Global_PassNum3=0; Global_SetPassCheck=3; break;
						case '1': Global_PassNum3=1; Global_SetPassCheck=3; break;
						case '2': Global_PassNum3=2; Global_SetPassCheck=3; break;
						case '3': Global_PassNum3=3; Global_SetPassCheck=3; break;
						case '4': Global_PassNum3=4; Global_SetPassCheck=3; break;
						case '5': Global_PassNum3=5; Global_SetPassCheck=3; break;
						case '6': Global_PassNum3=6; Global_SetPassCheck=3; break;
						case '7': Global_PassNum3=7; Global_SetPassCheck=3; break;
						case '8': Global_PassNum3=8; Global_SetPassCheck=3; break;
						case '9': Global_PassNum3=9; Global_SetPassCheck=3; break;
						default: /*TODO*/ break;
					}
			}
		else if(Global_SetPassCheck==3)
			{
				switch(Global_PressedKey)
					{
						case '0': Global_PassNum4=0; Global_SetPassCheck=4; break;
						case '1': Global_PassNum4=1; Global_SetPassCheck=4; break;
						case '2': Global_PassNum4=2; Global_SetPassCheck=4; break;
						case '3': Global_PassNum4=3; Global_SetPassCheck=4; break;
						case '4': Global_PassNum4=4; Global_SetPassCheck=4; break;
						case '5': Global_PassNum4=5; Global_SetPassCheck=4; break;
						case '6': Global_PassNum4=6; Global_SetPassCheck=4; break;
						case '7': Global_PassNum4=7; Global_SetPassCheck=4; break;
						case '8': Global_PassNum4=8; Global_SetPassCheck=4; break;
						case '9': Global_PassNum4=9; Global_SetPassCheck=4; break;
						default: /*TODO*/ break;
					}
			}
	}
	}


}

void Passward_Check(void)
{

	while (Global_SetPassCheck==4)
	{
	if (Global_PassNum1 == 1 && Global_PassNum2 == 1
		&& Global_PassNum3 == 1  && Global_PassNum4 == 1
		&& Global_SetPassCheck==4)
	{
		Global_SetPassCheck=CORRECT_PASS;
	}
	else
	{

		MSTK_voidDelayMs(2);
		HLCD_voidSendCommand(LCD_CLEAR);
			if (Global_Retry==3)
			{

				MSTK_voidDelayMs(35);
				HLCD_voidSendString("THIEF!!!");
				MSTK_voidDelayMs(15);
			}
			else if (Global_Retry<=3)
			{
				MSTK_voidDelayMs(10);
				HLCD_voidSendString("Try again");
				HLCD_voidGotoxy(0,1);
				MSTK_voidDelayMs(10);

			}
		MSTK_voidDelayMs(1000);
		Global_SetPassCheck=WRONG_PASS;
		Global_Retry++;
	}
	}
}

void Main_Menu (void)
{
	if(Global_SetPassCheck==CORRECT_PASS)
	{
		HLCD_voidSendCommand(LCD_CLEAR);
		MSTK_voidDelayMs(30);
		HLCD_voidSendString("1)Buzzer  2)LED");
		MSTK_voidDelayMs(30);
		HLCD_voidGotoxy(0,1);
		HLCD_voidSendString("3)Motor");
		Global_SetPassCheck++;
	}
	while (Global_SetPassCheck==6)
		{
			Global_PressedKey= KPD_u8GetPressedKey() ;
			if (Global_PressedKey!=0xFF)
				{
					switch(Global_PressedKey)
						{
							case '0': Global_ComponentSelection=0; 				 break;
							case '1': Global_ComponentSelection=BUZZER_MENUE; 	Global_SetPassCheck=7; break;
							case '2': Global_ComponentSelection=LED_MENUE; 		Global_SetPassCheck=7; break;
							case '3': Global_ComponentSelection=MOTOR_MENUE; 	Global_SetPassCheck=7; break;
							case '4': Global_ComponentSelection=4; 				break;
							case '5': Global_ComponentSelection=5; 				break;
							case '6': Global_ComponentSelection=6; 				break;
							case '7': Global_ComponentSelection=7; 				break;
							case '8': Global_ComponentSelection=8; 				break;
							case '9': Global_ComponentSelection=9; 				break;
							default: /*TODO*/ break;
						}
				}
		}

}

void User_Entery(void)
{
	u8 flag=0;
	u8 flag1=0;
	if (Global_SetPassCheck==7 && Global_ComponentSelection==BUZZER_MENUE)
	{
		HLCD_voidSendCommand(LCD_CLEAR);
		MSTK_voidDelayMs(30);
		HLCD_voidSendString("     BUZZER");
		MSTK_voidDelayMs(30);
		HLCD_voidGotoxy(0,1);
		HLCD_voidSendString("1-ON 2-OFF 3-Back");
	}
	else if (Global_SetPassCheck==7 && Global_ComponentSelection==LED_MENUE)
	{
		HLCD_voidSendCommand(LCD_CLEAR);
		MSTK_voidDelayMs(30);
		HLCD_voidSendString("       LED");
		MSTK_voidDelayMs(30);
		HLCD_voidGotoxy(0,1);
		HLCD_voidSendString("1-ON 2-OFF 3-Back");
	}
	else if (Global_SetPassCheck==7 && Global_ComponentSelection==MOTOR_MENUE)
		{
			HLCD_voidSendCommand(LCD_CLEAR);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("      MOTOR");
			MSTK_voidDelayMs(30);
			HLCD_voidGotoxy(0,1);
			HLCD_voidSendString("1-ON 2-OFF 3-Back");
		}
	while (Global_SetPassCheck==7)
	{
		Global_PressedKey= KPD_u8GetPressedKey() ;
		if (Global_PressedKey!=0xFF)
			{
				switch(Global_PressedKey)
					{
						case '0': Global_StateSelection=0; 							   break;
						case '1': Global_StateSelection=ON; 						   break;
						case '2': Global_StateSelection=OFF; 	                       break;
						case '3': Global_StateSelection=BACK; 	Global_SetPassCheck=5; break;
						case '4': Global_StateSelection=4;  						   break;
						case '5': Global_StateSelection=5; 							   break;
						case '6': Global_StateSelection=6;  						   break;
						case '7': Global_StateSelection=7; 							   break;
						case '8': Global_StateSelection=8;  						   break;
						case '9': Global_StateSelection=9; 							   break;
						default: /*TODO*/ break;
					}
			}
		if (Global_ComponentSelection==BUZZER_MENUE && Global_StateSelection==ON)
		{
			flag1=0;
			if (flag==0)
			{
				HLCD_voidSendCommand(LCD_CLEAR);
				flag=1;
			}
			else
			{

			}
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("    BUZZER ON..");
			HLCD_voidGotoxy(0,1);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("2)OFF 	   3)Back");
			Buzzer_On();
		}
		else if (Global_ComponentSelection==BUZZER_MENUE && Global_StateSelection==OFF)
		{
			flag=0;
			if (flag1==0)
				{
					HLCD_voidSendCommand(LCD_CLEAR);
					flag1=1;
				}
			else
			{

			}
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("  BUZZER OFF..");
			HLCD_voidGotoxy(0,1);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("1)ON      3)Back");
			//MSTK_voidDelayMs(350);
			Buzzer_Off();

		}
		else if (Global_ComponentSelection==BUZZER_MENUE && Global_StateSelection==BACK)
		{
			HLCD_voidSendCommand(LCD_CLEAR);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("    Loading..");
			MSTK_voidDelayMs(3000);
			Global_StateSelection=0;
		}


		if (Global_ComponentSelection==LED_MENUE && Global_StateSelection==ON)
		{
			flag1=0;
			if (flag==0)
				{
					HLCD_voidSendCommand(LCD_CLEAR);
					flag=1;
				}
				else
				{

				}
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("     LED ON..");
			HLCD_voidGotoxy(0,1);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("2)OFF 	   3)Back");
			Led_On();

		}
		else if (Global_ComponentSelection==LED_MENUE && Global_StateSelection==OFF)
		{
			flag=0;
			if (flag1==0)
				{
					HLCD_voidSendCommand(LCD_CLEAR);
					flag1=1;
				}
			else
				{

				}
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("    LED OFF..");
			HLCD_voidGotoxy(0,1);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("1)ON 	   3)Back");
			Led_Off();

		}
		else if (Global_ComponentSelection==LED_MENUE && Global_StateSelection==BACK)
		{
			HLCD_voidSendCommand(LCD_CLEAR);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("    Loading..");
			MSTK_voidDelayMs(3000);
			Global_StateSelection=0;
		}

		if (Global_ComponentSelection==MOTOR_MENUE && Global_StateSelection==ON)
		{
			flag1=0;
			if (flag==0)
			{
				HLCD_voidSendCommand(LCD_CLEAR);
				flag=1;
			}
			else
			{

			}
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("   MOTOR ON..");
			HLCD_voidGotoxy(0,1);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("2)OFF 	   3)Back");
			Motor_On();
		}
		else if (Global_ComponentSelection==MOTOR_MENUE && Global_StateSelection==OFF)
		{
			flag=0;
			if (flag1==0)
				{
					HLCD_voidSendCommand(LCD_CLEAR);
					flag1=1;
				}
			else
				{

				}
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("   MOTOR OFF..");
			HLCD_voidGotoxy(0,1);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("1)ON 	   3)Back");
			Motor_Off();
		}
		else if (Global_ComponentSelection==MOTOR_MENUE && Global_StateSelection==BACK)
		{
			HLCD_voidSendCommand(LCD_CLEAR);
			MSTK_voidDelayMs(30);
			HLCD_voidSendString("    Loading..");
			MSTK_voidDelayMs(3000);
			Global_StateSelection=0;
		}
	}

}
void Buzzer_On(void)
{
	MGPIO_voidSetPinValue(MGPIO_PORTA,PIN9,MGPIO_PIN_HIGH);
}
void Buzzer_Off(void)
{
	MGPIO_voidSetPinValue(MGPIO_PORTA,PIN9,MGPIO_PIN_LOW);
}

void Led_On(void)
{
	MGPIO_voidSetPinValue(MGPIO_PORTA,PIN8,MGPIO_PIN_HIGH);
}

void Led_Off(void)
{
	MGPIO_voidSetPinValue(MGPIO_PORTA,PIN8,MGPIO_PIN_LOW);
}

void Motor_On(void)
{
	MGPIO_voidSetPinValue(MGPIO_PORTA,PIN10,MGPIO_PIN_LOW);
}

void Motor_Off(void)
{
	MGPIO_voidSetPinValue(MGPIO_PORTA,PIN10,MGPIO_PIN_HIGH);
}
