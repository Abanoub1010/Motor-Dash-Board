/*
 * KPD_Program.c
 *
 *  Created on: Jan 28, 2023
 *      Author: Abanoub
 */
/*
 * KPD_Prog.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Abanoub
 */
#include "../include/LSTD_TYPES.h"
#include "../include/LERROR_STATES.h"
#include "../include/LBIT_MATH.h"
#include "../include/MGPIO_Interface.h"
#include "../include/MSTK_Interface.h"
#include "../include/KPD_Interface.h"
#include "../include/KPD_Config.h"



/*keypad matrix array*/
static const u8 KPD_au8Array[4][4]=
{
		{'1', '2', '3', '+'},
		{'4', '5', '6', '-'},
		{'7', '8', '9', '*'},
		{'/', '0', 'B', '='}
};

u8 KPD_u8GetPressedKey (void)
{

	u8 u8SwitchVal=NOT_PRESSED ;
	u8 u8Column;
	u8 u8Row;
	u8 ret;
	for(u8Column=0 ; u8Column<4 ; u8Column++)
	{
		MGPIO_voidSetPinValue(COLUMN_PORT,u8Column,MGPIO_PIN_LOW);

		for(u8Row=4 ; u8Row<8 ; u8Row++)
		{
			MGPIO_voidGetPinValue(ROW_PORT,u8Row,&ret);

			if (ret==MGPIO_PIN_LOW)
			{
				u8SwitchVal = KPD_au8Array[(7-u8Row)][u8Column] ;
				MGPIO_voidGetPinValue(ROW_PORT,u8Row,&ret);
				while (ret==MGPIO_PIN_LOW)
				{
					MGPIO_voidGetPinValue(ROW_PORT,u8Row,&ret);
				}

				MSTK_voidDelayMs(10);
				return u8SwitchVal;
			}

		}

		MGPIO_voidSetPinValue(COLUMN_PORT,u8Column,MGPIO_PIN_HIGH);
	}
	return u8SwitchVal;

}




