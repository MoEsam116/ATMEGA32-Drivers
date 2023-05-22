/*
 * Button.c
 *
 *  Created on: Apr 26, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:Button              */
/*      Version:1.00            */
/********************************/
/********************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"Button.h"

u8 Button_u8ButtonInit(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 Local_u8ErrorState = 0;
	DIO_u8SetPinDirection(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_INPUT);
	//setting pin direction as input
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_HIGH);
	//setting pin value as high
	//Now the internal pull up resistor in the mc is activated
	Local_u8ErrorState = 1;
	return Local_u8ErrorState;
}
u8 Button_u8ButtonGetValue(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 Local_u8PinValue=0;
	DIO_u8GetPinValue(Copy_u8Port,Copy_u8Pin,&Local_u8PinValue);
	return Local_u8PinValue;
}

