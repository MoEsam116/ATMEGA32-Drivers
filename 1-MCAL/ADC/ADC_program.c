/*
 * ADC_program.c
 *
 *  Created on: Jul 24, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:ADC                 */
/*      Version:1.00            */
/********************************/
/********************************/

#include"BIT_MATH.h"
#include"STD_TYPES.h"

#include"ADC_config.h"
#include"ADC_interface.h"
#include"ADC_private.h"
#include"ADC_register.h"

static u8 * ADC_pu8Reading = NULL;
static void (*ADC_pCallBackFunc)(void)=NULL;
static u8 ADC_u8BusyState=IDLE;
static u8 * ADC_pChainChannel = NULL;                    //global variable to carry chain array
static u8  ADC_ChainSize;                                // global variable to carry number of channels
static u16 * ADC_pChainResultArr=NULL;                   // global variable to carry result array
static u8  ADC_ChainIndex=0;
static u8 ADC_u8ISRSource;
void ADC_voidInit(void)
{
	// AVCC as ref voltage
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
	// activate left adjust result
	SET_BIT(ADMUX,ADMUX_ADLRA);
	// set prescaler to devide by 128
	SET_BIT(ADCSRA,ADCSRA_ADPS0);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS2);

	//enable prephiral
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}
u8 ADC_u8StartConversionSynch(u8 Local_u8Channel, u8 * Local_u8Reading)
{
	u8 Local_u8ErrorState=OK ;
	if(ADC_u8BusyState == IDLE){
		ADC_u8BusyState=BUSY;
		u32 Local_u32Counter=0;

		// clear the mux bits in admux register
		ADMUX &= 0b11100000;
		//set the required channel into the mux bits
		ADMUX |= Local_u8Channel;
		// start conversion
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		//polling busy waiting until the conversion complete flag is set or counter reaching timeout
		while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0)&&(Local_u32Counter<TIMEOUT))
		{
			Local_u32Counter ++ ;
		}
		if (Local_u32Counter == TIMEOUT)
		{
			// loop is broken because time out is reached
			Local_u8ErrorState =NOK ;
		}
		else
		{
			//loop is broken because flag is raised
			//clear the conversion complete flag
			SET_BIT(ADCSRA,ADCSRA_ADIF);
			ADC_u8BusyState=IDLE;
			*Local_u8Reading= ADCH;
		}


	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	// return the reading
	return Local_u8ErrorState;
}
u8 ADC_u8StartConversionAsynch(u8 Local_u8Channel, u8 * Local_u8Reading , void (*Local_pNotificationFunc)(void))
{u8 Local_u8ErrorState = OK ;
if(ADC_u8BusyState == IDLE){

	if ((Local_u8Reading == NULL )|| (Local_pNotificationFunc == NULL))
	{
		Local_u8ErrorState = NOK ;
	}
	else
	{
		ADC_u8BusyState=BUSY;
		ADC_u8ISRSource= SingleChannelAsync;
		// initialize the reading variable globally
		ADC_pu8Reading = Local_u8Reading;
		// initialize the call back notification function globally
		ADC_pCallBackFunc = Local_pNotificationFunc;

		// clear the mux bits in admux register
		ADMUX &= 0b11100000;
		//set the required channel into the mux bits
		ADMUX |= Local_u8Channel;
		// start conversion
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		// enable adc interrupt
		SET_BIT(ADCSRA,ADCSRA_ADIE);
	}
}
else
{
	Local_u8ErrorState = NOK;
}
return Local_u8ErrorState;
}
u8 ADC_u8StartChainAsynch(Chain_t *Local_Chain)
{
	u8 Local_u8ErrorState = OK ;
	//check null pointer
	if (Local_Chain == NULL)
	{
		Local_u8ErrorState = NOK;
	}
	else{
		if (ADC_u8BusyState == IDLE)
		{
			ADC_u8BusyState= BUSY;
			ADC_u8ISRSource= ChainAsync;
			//initialize chain channel array
			ADC_pChainChannel = Local_Chain->Channel;
			//initialize chain result array
			ADC_pChainResultArr = Local_Chain->Result;
			//initialize chain lenght
			ADC_ChainSize = Local_Chain->Size;
			//initialize chain notification function
			ADC_pCallBackFunc= Local_Chain->NotificationFunc;
			ADC_ChainIndex=0;
			//set required channel
			ADMUX &= 0b11100000;\
			ADMUX |=ADC_pChainChannel[ADC_ChainIndex];
			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			//enable interrupt
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	return Local_u8ErrorState;
}
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ISRSource == SingleChannelAsync){
		ADC_u8BusyState = IDLE;
		//read adc result
		*ADC_pu8Reading = ADCH;
		// invoke the callback notification function
		ADC_pCallBackFunc();
		// disable conversion complete interrupt
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if (ADC_u8ISRSource == ChainAsync)
	{
		//read the current conversion
		ADC_pChainResultArr[ADC_ChainIndex]=ADCH ;
		//increment index
		ADC_ChainIndex++;
		//check chain is finished or not
		if(ADC_ChainIndex == ADC_ChainSize)
		{
			//chain is finished
			//adc is now idle
			ADC_u8BusyState=IDLE;
			//invoke the call back function
			ADC_pCallBackFunc();
			//disable interrupt
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			//chain is not finished
			ADMUX&=0b11100000;
			ADMUX|=ADC_pChainChannel[ADC_ChainIndex];
			//start conv
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}
