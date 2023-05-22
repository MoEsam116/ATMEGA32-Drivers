/*
 * LED.c
 *
 *  Created on: Apr 27, 2023
 *      Author: essam
 */
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:LED                 */
/*      Version:1.00            */
/********************************/
/********************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LED.h"

u8 LED_u8LedOn(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Connection)
{
	u8 Local_u8ErrorState = 0;
	DIO_u8SetPinDirection(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_OUTPUT);
	if(Copy_u8Connection==SRC)
	{
		DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_HIGH);
	}
	else if(Copy_u8Connection==SINK)
	{
		DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_LOW);
	}
	else
	{
		Local_u8ErrorState = 1;
	}


	Local_u8ErrorState = 1;
	return Local_u8ErrorState;
}
u8 LED_u8LedOff(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Connection)
{
	u8 Local_u8ErrorState = 0;
		DIO_u8SetPinDirection(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_OUTPUT);
		if(Copy_u8Connection==SRC)
		{
			DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_LOW);
		}
		else if(Copy_u8Connection==SINK)
		{
			DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_HIGH);
		}
		else
		{
			Local_u8ErrorState = 1;
		}


		Local_u8ErrorState = 1;
		return Local_u8ErrorState;
}
