/*
 * WDT_program.c
 *
 *  Created on: Aug 26, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:WDT                 */
/*      Version:1.00            */
/********************************/
/********************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WDT_interface.h"
#include "WDT_register.h"

void WDT_voidSleep(u8 Local_u8SleepTime)
{
	/*Clear The prescaler Mask*/
	WDTCR &= 0b11111000;

	/*Set the requered prescaler*/
	WDTCR |= Local_u8SleepTime;
}
void WDT_voidEnable(void)
{
	SET_BIT(WDTCR,WDTCR_WDE);
}
void WDT_voidDisable(void)
{
	WDTCR |= 0b00011000;
	WDTCR=0;
}
