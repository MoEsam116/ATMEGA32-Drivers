/*
 * Timer_program.c
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

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Timer_interface.h"
#include "Timer_private.h"
#include "Timer_register.h"
#include "Timer_config.h"

static void (*pvCallBackFuncs[NumberOfINTs])(void)= {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL} ;

void TIMER0_VoidInit(u8 TIMER0_MODE)
{
	/********************************Normal MODE*************************************************/
	if(TIMER0_MODE == TIMER0_NormalMode)
	{
		/*Set wave generation mode*/
		CLR_BIT(TIMER0_TCCR0,TCCR0_WGM00);
		CLR_BIT(TIMER0_TCCR0,TCCR0_WGM01);
		/*Enable Interrupt*/
		SET_BIT(TIMER0_TIMSK,TIMSK_TOIE0);
	}
	/********************************FAST PWM*************************************************/
	else if (TIMER0_MODE == TIMER0_FastPWMMode)	//TO use this mode PIN OC0 Must be defined as OUTPUT in APP
	{
		/*SET WGM*/
		SET_BIT(TIMER0_TCCR0,TCCR0_WGM00);
		SET_BIT(TIMER0_TCCR0,TCCR0_WGM01);
		/*SET Compare output mode*/
#if TIMER0_CompareOutputMode == TIMER0_CompareModeFastPWMOFF
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM00);
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM01);
#elif 	TIMER0_CompareOutputMode == TIMER0_CompareModeFastPWMInverted
		SET_BIT(TIMER0_TCCR0,TCCR0_COM00);
		SET_BIT(TIMER0_TCCR0,TCCR0_COM01);
#elif 	TIMER0_CompareOutputMode == TIMER0_CompareModeFastPWMNonInverted
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM00);
		SET_BIT(TIMER0_TCCR0,TCCR0_COM01);
#endif


	}
	/*********************************PWM Phase Correct****************************************/
	else if (TIMER0_MODE	==	TIMER0_PWMPhaseCorrectMode)
	{
		/*SET WGM*/
		SET_BIT(TIMER0_TCCR0,TCCR0_WGM00);
		CLR_BIT(TIMER0_TCCR0,TCCR0_WGM01);
		/*SET Compare output mode*/
#if TIMER0_CompareOutputMode == TIMER0_CompareModePhaseCorrectPWMOFF
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM00);
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM01);
#elif 	TIMER0_CompareOutputMode == TIMER0_CompareModePhaseCorrectPWMInverted
		SET_BIT(TIMER0_TCCR0,TCCR0_COM00);
		SET_BIT(TIMER0_TCCR0,TCCR0_COM01);
#elif 	TIMER0_CompareOutputMode == TIMER0_CompareModePhaseCorrectPWMNonInverted
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM00);
		SET_BIT(TIMER0_TCCR0,TCCR0_COM01);
#endif



	}
	/***********************************CTC MODE***********************************************/
	else if (TIMER0_MODE	==	TIMER0_CTCMode)
	{
		/*SET WGM*/
		CLR_BIT(TIMER0_TCCR0,TCCR0_WGM00);
		SET_BIT(TIMER0_TCCR0,TCCR0_WGM01);
		/*SET Compare output mode*/
#if TIMER0_CompareOutputMode == TIMER0_CompareModeOFF
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM00);
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM01);
#elif 	TIMER0_CompareOutputMode == TIMER0_CompareModeSET
		SET_BIT(TIMER0_TCCR0,TCCR0_COM00);
		SET_BIT(TIMER0_TCCR0,TCCR0_COM01);
#elif 	TIMER0_CompareOutputMode == TIMER0_CompareModeCLR
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM00);
		SET_BIT(TIMER0_TCCR0,TCCR0_COM01);
#elif 	TIMER0_CompareOutputMode == TIMER0_CompareModeTOGGLE
		SET_BIT(TIMER0_TCCR0,TCCR0_COM00);
		CLR_BIT(TIMER0_TCCR0,TCCR0_COM01);

#endif

		/*Enable Interrupt*/
		SET_BIT(TIMER0_TIMSK,TIMSK_OCIE0);
	}
	/*Set PRESCALER*/
#if	TIMER0_PRESCALER_MODE	== TIMER0_PRESCALER_NOCS

	TIMER0_TCCR0	&=	PRESCALER_MASK	;
	TIMER0_TCCR0	|=	TIMER0_PRESCALER_NOCS	;
#elif	TIMER0_PRESCALER_MODE	== TIMER0_PRESCALER_NoPS

	TIMER0_TCCR0	&=	PRESCALER_MASK	;
	TIMER0_TCCR0	|=	TIMER0_PRESCALER_NoPS	;
#elif	TIMER0_PRESCALER_MODE	== TIMER0_PRESCALER_8

	TIMER0_TCCR0	&=	PRESCALER_MASK	;
	TIMER0_TCCR0	|=	TIMER0_PRESCALER_8	;
#elif	TIMER0_PRESCALER_MODE	== TIMER0_PRESCALER_64

	TIMER0_TCCR0	&=	PRESCALER_MASK	;
	TIMER0_TCCR0	|=	TIMER0_PRESCALER_64	;
#elif	TIMER0_PRESCALER_MODE	== TIMER0_PRESCALER_256

	TIMER0_TCCR0	&=	PRESCALER_MASK	;
	TIMER0_TCCR0	|=	TIMER0_PRESCALER_256	;
#elif	TIMER0_PRESCALER_MODE	== TIMER0_PRESCALER_1024

	TIMER0_TCCR0	&=	PRESCALER_MASK	;
	TIMER0_TCCR0	|=	TIMER0_PRESCALER_1024	;
#elif	TIMER0_PRESCALER_MODE	== TIMER0_PRESCALER_CountFalling

	TIMER0_TCCR0	&=	PRESCALER_MASK	;
	TIMER0_TCCR0	|=	TIMER0_PRESCALER_CountFalling	;
#elif	TIMER0_PRESCALER_MODE	== TIMER0_PRESCALER_CountRising

	TIMER0_TCCR0	&=	PRESCALER_MASK	;
	TIMER0_TCCR0	|=	TIMER0_PRESCALER_Rising	;
#endif
}




void TIMER1_VoidInit(u8 TIMER1_MODE)
{
	if (TIMER1_MODE 	==	TIMER1_NormalMode)
	{
		/*SET WGM*/
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TCCR1B_WGM13);

		/*Enable Interrupt*/
		SET_BIT(TIMER1_TIMSK,TIMSK_TOIE1);
	}
	else if (TIMER1_MODE == TIMER1_FastPWMOnICR1Mode)
	{
		/*To Use this function PIN OC1A/OC1B MUST be connected as output
		 AND ICR1 Value must be set to a value using function	TIMER1_VoidSetICRValue(u16 Value) */

		/*SET WGM*/
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TCCR1B_WGM13);
		/*SET Compare output mode*/
#if TIMER1_CompareOutputMode == TIMER1_CompareModeFastPWMOffChannelA
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeFastPWMInvertedChannelA
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeFastPWMNonInvertedChannelA
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);
#elif TIMER1_CompareOutputMode == TIMER1_CompareModeFastPWMOffChannelB
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeFastPWMInvertedChannelB
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeFastPWMNonInvertedChannelB
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#endif

	}
	else if (TIMER1_MODE == TIMER1_CTCOnOCR1AMode)
	{
		/*OCR1A Value must be set with function TIMER_VoidSetCompareMatchValue	to generate interrupt
		 * when TCNT1 value = OCR1A Value*/

		/*SET WGM*/
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TCCR1B_WGM13);
		/*SET Compare output mode*/
#if TIMER1_CompareOutputMode == TIMER1_CompareModeOFFChannelA
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeSETChannelA
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeCLRChannelA
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);
#elif TIMER1_CompareOutputMode == TIMER1_CompareModeTOGGLEChannelA
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);

#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeOFFChannelB
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeSETChannelB
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeCLRChannelB
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeTOGGLEChannelB
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#endif

		/*Enable Interrupt */
		SET_BIT(TIMER1_TIMSK,TIMSK_OCIE1A);
	}
	else if (TIMER1_MODE == TIMER1_CTCOnOCR1BMode)
	{
		/*OCR1A Value must be set with function TIMER_VoidSetCompareMatchValue	to generate interrupt
		 * when TCNT1 value = OCR1A Value*/

		/*SET WGM*/
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TCCR1B_WGM13);
		/*SET Compare output mode*/
#if TIMER1_CompareOutputMode == TIMER1_CompareModeOFFChannelA
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeSETChannelA
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeCLRChannelA
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);
#elif TIMER1_CompareOutputMode == TIMER1_CompareModeTOGGLEChannelA
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1A1);

#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeOFFChannelB
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeSETChannelB
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeCLRChannelB
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#elif 	TIMER1_CompareOutputMode == TIMER1_CompareModeTOGGLEChannelB
		SET_BIT(TIMER1_TCCR1A,TCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TCCR1A_COM1B1);
#endif
		/*Enable Interrupt */
		SET_BIT(TIMER1_TIMSK,TIMSK_OCIE1B);
	}
	/*SET PRESCALER*/
	#if	TIMER1_PRESCALER_MODE	== TIMER1_PRESCALER_NOCS

			TIMER1_TCCR1B	&=	PRESCALER_MASK	;
			TIMER1_TCCR1B	|=	TIMER1_PRESCALER_NOCS	;
	#elif	TIMER1_PRESCALER_MODE	== TIMER1_PRESCALER_NoPS

			TIMER1_TCCR1B	&=	PRESCALER_MASK	;
			TIMER1_TCCR1B	|=	TIMER1_PRESCALER_NoPS	;
	#elif	TIMER1_PRESCALER_MODE	== TIMER1_PRESCALER_8

			TIMER1_TCCR1B	&=	PRESCALER_MASK	;
			TIMER1_TCCR1B	|=	TIMER1_PRESCALER_8	;
	#elif	TIMER1_PRESCALER_MODE	== TIMER1_PRESCALER_64

			TIMER1_TCCR1B	&=	PRESCALER_MASK	;
			TIMER1_TCCR1B	|=	TIMER1_PRESCALER_64	;
	#elif	TIMER1_PRESCALER_MODE	== TIMER1_PRESCALER_256

			TIMER1_TCCR1B	&=	PRESCALER_MASK	;
			TIMER1_TCCR1B	|=	TIMER1_PRESCALER_256	;
	#elif	TIMER1_PRESCALER_MODE	== TIMER1_PRESCALER_1124

			TIMER1_TCCR1B	&=	PRESCALER_MASK	;
			TIMER1_TCCR1B	|=	TIMER1_PRESCALER_1124	;
	#elif	TIMER1_PRESCALER_MODE	== TIMER1_PRESCALER_CountFalling

			TIMER1_TCCR1B	&=	PRESCALER_MASK	;
			TIMER1_TCCR1B	|=	TIMER1_PRESCALER_CountFalling	;
	#elif	TIMER1_PRESCALER_MODE	== TIMER1_PRESCALER_CountRising

			TIMER1_TCCR1B	&=	PRESCALER_MASK	;
			TIMER1_TCCR1B	|=	TIMER1_PRESCALER_Rising	;
	#endif

}


void TIMER_SetCallBackFunc	(u8 INT_ID  , void (*Copy_pvFunc)(void)	)
{
	if  (	(INT_ID 	== TIMER0_OVFINT)	&&	(Copy_pvFunc	!= 	NULL))
	{
		pvCallBackFuncs[TIMER0_OVFINT]	=	Copy_pvFunc;
	}
	else if (	(INT_ID 	== TIMER0_COMPINT)	&& (Copy_pvFunc	!= 	NULL))
	{
		pvCallBackFuncs[TIMER0_COMPINT]	=	Copy_pvFunc;
	}
	else if (	(INT_ID 	== TIMER1_OVFINT)	&& (Copy_pvFunc	!= 	NULL))
	{
		pvCallBackFuncs[TIMER1_OVFINT]	=	Copy_pvFunc;
	}
	else if (	(INT_ID 	== TIMER1_COMPBINT)	&& (Copy_pvFunc	!= 	NULL))
	{
		pvCallBackFuncs[TIMER1_COMPBINT]	=	Copy_pvFunc;
	}
	else if (	(INT_ID 	== TIMER1_COMPAINT)	&& (Copy_pvFunc	!= 	NULL))
	{
		pvCallBackFuncs[TIMER1_COMPAINT]	=	Copy_pvFunc;
	}
	else if (	(INT_ID 	== TIMER1_CAPTINT)	&& (Copy_pvFunc	!= 	NULL))
	{
		pvCallBackFuncs[TIMER1_CAPTINT]	=	Copy_pvFunc;
	}
	else if (	(INT_ID 	== TIMER2_OVFINT)	&& (Copy_pvFunc	!= 	NULL))
	{
		pvCallBackFuncs[TIMER2_OVFINT]	=	Copy_pvFunc;
	}
	else if (	(INT_ID 	== TIMER2_COMPINT)	&& (Copy_pvFunc	!= 	NULL))
	{
		pvCallBackFuncs[TIMER2_COMPINT]	=	Copy_pvFunc;
	}
}

void TIMER0_voidStop  ( void )
{
	TIMER0_TCCR0 |= (0x00) ;
}


void TIMER_voidSetPreLoadValue	(u8 TIMER_ID , u16 Local_Value)
{
	switch (TIMER_ID)
	{
	case TIMER0:	TIMER0_TCNT0	= (u8)Local_Value ;				break;
	case TIMER1:	TIMER1_TCNT1	=	  Local_Value ;				break;
	case TIMER2:	TIMER2_TCNT2	= Local_Value ;					break;

	}
}

void TIMER_VoidSetCompareMatchValue	(u8 TIMER_ID , u16 Local_Value)
{
	switch (TIMER_ID)
	{
	case TIMER0:	if (Local_Value<256 ){TIMER0_OCR0	= Local_Value ;}	break;
	case TIMER1A:	TIMER1_OCR1A=	  Local_Value ;							break;
	case TIMER1B:	TIMER1_OCR1B=	  Local_Value ;							break;
	case TIMER2:	if (Local_Value<256 ){TIMER2_OCR2	= Local_Value ;}	break;

	}
}
void TIMER_VoidSetPWMDuty	(u8 TIMER_ID , u16 Local_Value)
{
	switch (TIMER_ID)
	{
	case TIMER0:	if (Local_Value<256 ){TIMER0_OCR0	= 	  (u8)Local_Value ;}	break;
	case TIMER1A:	TIMER1_OCR1A=	  Local_Value ;									break;
	case TIMER1B:	TIMER1_OCR1B=	  Local_Value ;									break;
	case TIMER2:	if (Local_Value<256 ){TIMER2_OCR2	= 	  Local_Value ;}		break;

	}
}
void TIMER1_VoidSetICRValue( u16 Local_u16ICRValue)
{
	TIMER1_ICR1	=	Local_u16ICRValue	;
}
void ICU_VoidInit(void)
{
	/*Set triggered edge initially to Rising edge*/
	SET_BIT(TIMER1_TCCR1B,TCCR1B_ICES1);
	/*Enable input capture interrupt*/
	SET_BIT(TIMER1_TIMSK,TIMSK_TICIE1);
}
void ICU_voidSetInterruptState(u8 state)
{
	if(state == Enabled)
	{
		SET_BIT(TIMER1_TIMSK,TIMSK_TICIE1);
	}
	else if (state == Disabled)
	{
		CLR_BIT(TIMER1_TIMSK,TIMSK_TICIE1);
	}
}
u16 ICU_u16ReadInputCapture(void)
{
	return TIMER1_ICR1;
}
void ICU_SetEdgeAsTrigger(u8 Local_u8Edge)
{
	if (Local_u8Edge == ICU_Rising_Edge	)
	{
		SET_BIT(TIMER1_TCCR1B,TCCR1B_ICES1);
	}
	else if (Local_u8Edge 	== ICU_Falling_Edge )
	{
		CLR_BIT(TIMER1_TCCR1B,TCCR1B_ICES1);
	}
}
/******************************ISR Functions*****************************************/
void __vector_11 (void)			__attribute__((signal));
void __vector_11 (void)
{

	if (	(pvCallBackFuncs[TIMER0_OVFINT]	!= NULL) )
	{
		pvCallBackFuncs[TIMER0_OVFINT]();
	}

}
void __vector_10 (void)			__attribute__((signal));
void __vector_10 (void)
{
	if (	(pvCallBackFuncs[TIMER0_COMPINT]	!= NULL) )
	{
		pvCallBackFuncs[TIMER0_COMPINT]();
	}
}
void __vector_9 (void)	__attribute__((signal));
void __vector_9 (void)
{
	if (	(pvCallBackFuncs[TIMER1_OVFINT]	!= NULL)  )
	{
		pvCallBackFuncs[TIMER1_OVFINT]();
	}

}
void __vector_8 (void)	__attribute__((signal));
void __vector_8 (void)
{
	if (	(pvCallBackFuncs[TIMER1_COMPBINT]	!= NULL)  )
	{
		pvCallBackFuncs[TIMER1_COMPBINT]();
	}

}
void __vector_7 (void)	__attribute__((signal));
void __vector_7 (void)
{
	if (	(pvCallBackFuncs[TIMER1_COMPAINT]	!= NULL)  )
	{
		pvCallBackFuncs[TIMER1_COMPAINT]();
	}

}
void __vector_6 (void)	__attribute__((signal));
void __vector_6 (void)
{
	if (	(pvCallBackFuncs[TIMER1_CAPTINT]	!= NULL)  )
	{
		pvCallBackFuncs[TIMER1_CAPTINT]();
	}

}
void __vector_5 (void)	__attribute__((signal));
void __vector_5 (void)
{
	if (	(pvCallBackFuncs[TIMER2_OVFINT]	!= NULL)  )
	{
		pvCallBackFuncs[TIMER2_OVFINT]();
	}

}
void __vector_4 (void)	__attribute__((signal));
void __vector_4 (void)
{
	if (	(pvCallBackFuncs[TIMER2_COMPINT]	!= NULL)  )
	{
		pvCallBackFuncs[TIMER2_COMPINT]();
	}

}
