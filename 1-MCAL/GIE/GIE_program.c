/*
 * GIE_program.c
 *
 *  Created on: May 20, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:GIE                 */
/*      Version:1.00            */
/********************************/
/********************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"GIE_register.h"
#include"GIE_interface.h"

void GIE_voidGIEEnable(void)
{
	SET_BIT(SREG,SREG_GIE);
}

void GIE_voidGIEDisable(void)
{
	CLR_BIT(SREG,SREG_GIE);
}
