/*
 * Timer_interface.h
 *
 *  Created on: Aug 26, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:TIMER               */
/*      Version:1.00            */
/********************************/
/********************************/
#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_VoidInit(u8 TIMER0_MODE);
void TIMER1_VoidInit(u8 TIMER1_MODE);

void TIMER_SetCallBackFunc(u8 TIMER_ID,void (*Copy_pvFunc)(void));

void TIMER_voidSetPreLoadValue(u8 TIMER_ID,u16 Local_Value);

void TIMER_VoidSetCompareMatchValue(u8 TIMER_ID,u16 Local_Value);

void TIMER_VoidSetPWMDuty(u8 TIMER_ID,u16 Local_Value);

void TIMER1_VoidSetICRValue(u16 Local_u16ICRValue);

void ICU_VoidInit(void);

void ICU_SetEdgeAsTrigger(u8 Local_u8Edge);

u16 ICU_u16ReadInputCapture(void);

void ICU_voidSetInterruptState(u8 state);

void TIMER0_voidStop(void);

#endif /* TIMER_INTERFACE_H_ */
