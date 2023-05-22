/*
 * EXTI_program.c
 *
 *  Created on: May 19, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:EXTI                */
/*      Version:1.00            */
/********************************/
/********************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"EXTI_interface.h"
#include"EXTI_register.h"
#include"EXTI_private.h"
#include"EXTI_config.h"

/*Global pointers to functions to hold INT0,INT1 and INT2 ISR's addresses*/
void(*EXTI_pvINT0Func)(void)=NULL;
void(*EXTI_pvINT1Func)(void)=NULL;
void(*EXTI_pvINT2Func)(void)=NULL;

void EXTI_voidInt0Init(void)
{
	/*1-check sense control*/
#if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error "wrong INT0_SENSE configuration option"
#endif

	/*check peripheral interrupt enable initial state*/
#if INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);

#elif INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);

#else
#error "wrong INT0_INITIAL_STATE configuration option"
#endif

}

void EXTI_voidInt1Init(void)
{
	/*1-check sense control*/
#if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#else
#error "wrong INT1_SENSE configuration option"
#endif

	/*check peripheral interrupt enable initial state*/
#if INT1_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);

#elif INT1_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);

#else
#error "wrong INT1_INITIAL_STATE configuration option"
#endif

}

void EXTI_voidInt2Init(void)
{
	/*1-check sense control*/

#if INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);

#elif INT2_SENSE == RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);

#else
#error "wrong INT2_SENSE configuration option"
#endif

	/*check peripheral interrupt enable initial state*/
#if INT2_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);

#elif INT2_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);

#else
#error "wrong INT2_INITIAL_STATE configuration option"
#endif

}

u8 EXTI_u8INT0SenseControl(u8 Copy_u8Sense)
{
	u8 Localu8ErrorState=OK;
	switch(Copy_u8Sense)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);
		break;
	case ON_CHANGE:
		SET_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);
		break;
	case FALLING_EDGE:
		CLR_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);
		break;
	case RISING_EDGE:
		SET_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);
		break;
	default :Localu8ErrorState=NOK;
	}
	return Localu8ErrorState;
}

u8 EXTI_u8INT1SenseControl(u8 Copy_u8Sense)
{
	u8 Localu8ErrorState=OK;
	switch(Copy_u8Sense)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR,MCUCR_ISC10);
		CLR_BIT(MCUCR,MCUCR_ISC11);
		break;
	case ON_CHANGE:
		SET_BIT(MCUCR,MCUCR_ISC10);
		CLR_BIT(MCUCR,MCUCR_ISC11);
		break;
	case FALLING_EDGE:
		CLR_BIT(MCUCR,MCUCR_ISC10);
		SET_BIT(MCUCR,MCUCR_ISC11);
		break;
	case RISING_EDGE:
		SET_BIT(MCUCR,MCUCR_ISC10);
		SET_BIT(MCUCR,MCUCR_ISC11);
		break;
	default :Localu8ErrorState=NOK;
	}
	return Localu8ErrorState;
}

u8 EXTI_u8INT2SenseControl(u8 Copy_u8Sense)
{
	u8 Localu8ErrorState=OK;
	switch(Copy_u8Sense)
	{
	case FALLING_EDGE:
		 CLR_BIT(MCUCSR,MCUCSR_ISC2);
	break;
	case RISING_EDGE:
		 SET_BIT(MCUCSR,MCUCSR_ISC2);
	break;
	default :Localu8ErrorState=NOK;
	}
	return Localu8ErrorState;
}

u8 EXTI_u8INTEnable(u8 Copy_u8INTNumber)
{
	u8 Localu8ErrorState=OK;
	switch(Copy_u8INTNumber)
	{
    case INT0:	SET_BIT(GICR,GICR_INT0);	break;
	case INT1:	SET_BIT(GICR,GICR_INT1);	break;
	case INT2:	SET_BIT(GICR,GICR_INT2);	break;
	default :Localu8ErrorState=NOK;
	}
	return Localu8ErrorState;
}

u8 EXTI_u8INTDisable(u8 Copy_u8INTNumber)
{
	u8 Localu8ErrorState;
	switch(Copy_u8INTNumber)
	{
    case INT0:	CLR_BIT(GICR,GICR_INT0);	break;
	case INT1:	CLR_BIT(GICR,GICR_INT1);	break;
	case INT2:	CLR_BIT(GICR,GICR_INT2);	break;
	default :Localu8ErrorState=NOK;
	}
	return Localu8ErrorState;
}

u8 EXTI_u8INT0SetCallBack(void(*Copy_pvINT0Func)(void))
{
	u8 Localu8ErrorState;
	if(Copy_pvINT0Func != NULL)
	{
		EXTI_pvINT0Func=Copy_pvINT0Func;
	}
	else
	{
		Localu8ErrorState=NULL_POINTER;
	}
	return Localu8ErrorState;
}

u8 EXTI_u8INT1SetCallBack(void(*Copy_pvINT1Func)(void))
{
	u8 Localu8ErrorState;
		if(Copy_pvINT1Func != NULL)
		{
			EXTI_pvINT1Func=Copy_pvINT1Func;
		}
		else
		{
			Localu8ErrorState=NULL_POINTER;
		}
		return Localu8ErrorState;
}

u8 EXTI_u8INT2SetCallBack(void(*Copy_pvINT2Func)(void))
{
	u8 Localu8ErrorState;
		if(Copy_pvINT2Func != NULL)
		{
			EXTI_pvINT2Func=Copy_pvINT2Func;
		}
		else
		{
			Localu8ErrorState=NULL_POINTER;
		}
		return Localu8ErrorState;
}

/*ISR of INT0*/
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if(EXTI_pvINT0Func != NULL)
	{
	EXTI_pvINT0Func();
	}
	else
	{
		//Do nothing
	}
}

/*ISR of INT1*/
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if(EXTI_pvINT1Func != NULL)
		{
		EXTI_pvINT1Func();
		}
		else
		{
			//Do nothing
		}
}

/*ISR of INT2*/
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if(EXTI_pvINT2Func != NULL)
		{
		EXTI_pvINT2Func();
		}
		else
		{
			//Do nothing
		}
}

