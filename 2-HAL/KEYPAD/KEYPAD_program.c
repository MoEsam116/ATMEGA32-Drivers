/*
 * KEYPAD_program.c
 *
 *  Created on: May 11, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:KEYPAD              */
/*      Version:1.00            */
/********************************/
/********************************/

#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"KEYPAD_config.h"
#include"KEYPAD_interface.h"
#include"KEYPAD_private.h"

void KEYPAD_voidInit()
{
	/*setting row pins as input*/
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_ROW0,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_ROW1,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_ROW2,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_ROW3,DIO_u8PIN_INPUT);
	/*activate pull up resistor*/
	DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_ROW0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_ROW1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_ROW2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_ROW3,DIO_u8PIN_HIGH);
	/*setting column pins as output*/
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_COL0,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_COL1,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_COL2,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_COL3,DIO_u8PIN_OUTPUT);
	/*setting columns pins as high*/
	DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_COL0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_COL1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_COL2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_COL3,DIO_u8PIN_HIGH);
}

u8 KEYPAD_u8GetPressedButton()
{
	u8 Local_u8PressedKey=KEYPAD_NO_BUTTON_PRESSED,Local_u8RowIndex,Local_u8ColumnIndex,Local_u8PinState;
	static u8 Local_u8KEYPADArr[KEYPAD_ROW_NUM][KEYPAD_COL_NUM]=KEYPAD_BUTTON_ARR;
	static u8 Local_u8KEYPADColumnArr[KEYPAD_COL_NUM]={KEYPAD_COL0,KEYPAD_COL1,KEYPAD_COL2,KEYPAD_COL3};
	static u8 Local_u8KEYPADRowArr[KEYPAD_COL_NUM]={KEYPAD_ROW0,KEYPAD_ROW1,KEYPAD_ROW2,KEYPAD_ROW3};
	for(Local_u8ColumnIndex=0;Local_u8ColumnIndex<KEYPAD_COL_NUM;Local_u8ColumnIndex++)
	{
		/*activate current column*/
		DIO_u8SetPinValue(KEYPAD_PORT,Local_u8KEYPADColumnArr[Local_u8ColumnIndex],DIO_u8PIN_LOW);
		for(Local_u8RowIndex=0;Local_u8RowIndex<KEYPAD_ROW_NUM;Local_u8RowIndex++)
		{
			/*read the current row*/
			DIO_u8GetPinValue(KEYPAD_PORT,Local_u8KEYPADRowArr[Local_u8RowIndex],&Local_u8PinState);
			/*check if switch is pressed*/
			if(DIO_u8PIN_LOW==Local_u8PinState)
			{
				Local_u8PressedKey=Local_u8KEYPADArr[Local_u8RowIndex][Local_u8ColumnIndex];
				/*polling(busy waiting until key is released)*/
				while(DIO_u8PIN_LOW==Local_u8PinState)
				{
					DIO_u8GetPinValue(KEYPAD_PORT,Local_u8KEYPADRowArr[Local_u8RowIndex],&Local_u8PinState);
				}
				return Local_u8PressedKey;
			}
		}
		/*deactivate the current column*/
		DIO_u8SetPinValue(KEYPAD_PORT,Local_u8KEYPADColumnArr[Local_u8ColumnIndex],DIO_u8PIN_HIGH);
	}
	return Local_u8PressedKey;
}
