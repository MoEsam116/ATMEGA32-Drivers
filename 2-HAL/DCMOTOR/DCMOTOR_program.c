/*
 * DCMOTOR_program.c
 *
 *  Created on: May 13, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:DCMOTOR             */
/*      Version:1.00            */
/********************************/
/********************************/

#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"DCMOTOR_config.h"
#include"DCMOTOR_interface.h"
#include"DIO_interface.h"

void DCMOTOR_voidDCMOTORInit()
{
	/*setting motor pins as output*/
	DIO_u8SetPinDirection(DCMOTOR_PORT,DCMOTOR_CW_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DCMOTOR_PORT,DCMOTOR_CCW_PIN,DIO_u8PIN_OUTPUT);
}

void DCMOTOR_voidDCMOTORRotateCW()
{
	/*setting CW pin as high and setting CCW pin as low*/
	DIO_u8SetPinValue(DCMOTOR_PORT,DCMOTOR_CW_PIN,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DCMOTOR_PORT,DCMOTOR_CCW_PIN,DIO_u8PIN_LOW);
}

void DCMOTOR_voidDCMOTORRotateCCW()
{
	/*setting CCW pin as high and setting CW pin as low*/
	DIO_u8SetPinValue(DCMOTOR_PORT,DCMOTOR_CW_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCMOTOR_PORT,DCMOTOR_CCW_PIN,DIO_u8PIN_HIGH);
}

void DCMOTOR_voidMOTORStop()
{
	/*motor stops moving*/
	DIO_u8SetPinValue(DCMOTOR_PORT,DCMOTOR_CW_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCMOTOR_PORT,DCMOTOR_CCW_PIN,DIO_u8PIN_LOW);
}

