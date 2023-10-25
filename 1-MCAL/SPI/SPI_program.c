/*
 * SPI_program.c
 *
 *  Created on: Oct 25, 2023
 *      Author: essam
 */
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:SPI                 */
/*      Version:1.00            */
/********************************/
/********************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"SPI_config.h"
#include"SPI_inerface.h"
#include"SPI_private.h"
#include"SPI_register.h"

void SPI_voidInitMaster(void)
{

	/* SPI Peripheral Interrupt Enable */
#if   SPI_INTERRUPT ==   ENABLED
	SET_BIT( SPCR , SPCR_SPIE ) ;
#elif SPI_INTERRUPT ==   DISABLED
	CLR_BIT( SPCR , SPCR_SPIE ) ;
#endif

	/* Data Order Configuration */
#if   DATA_ORDER   ==   LSB_FIRST
	SET_BIT( SPCR , SPCR_DORD ) ;
#elif DATA_ORDER   ==   MSB_FIRST
	CLR_BIT( SPCR , SPCR_DORD ) ;
#endif

	/* Master Initialization */
	SET_BIT( SPCR , SPCR_MSTR ) ;

	/* Clock Polarity */
#if   CLOCK_POLARITY_MODE  ==  IDLE_HIGH
	SET_BIT( SPCR , SPCR_CPOL ) ;
#elif CLOCK_POLARITY_MODE  ==  IDLE_LOW
	CLR_BIT( SPCR , SPCR_CPOL ) ;
#endif

	/* Clock Phase */
#if   CLOCK_PHASE_MODE  ==  SETUP_FIRST
	SET_BIT( SPCR , SPCR_CPHA ) ;
#elif CLOCK_PHASE_MODE  ==  SAMPLE_FIRST
	CLR_BIT( SPCR , SPCR_CPHA ) ;
#endif

	/* Clock Rate Select */
#if ( CLOCK_RATE_SELECT >= FREQ_DIVIDE_BY_4 )  &&  ( CLOCK_RATE_SELECT <= FREQ_DIVIDE_BY_128 )

	/* Clear Double Speed Bit */
	CLR_BIT( SPSR , SPSR_SPI2X ) ;
	/* Bit Masking Clock Select */
	SPCR &= ( CLOCK_MASK ) ;
	SPCR |= ( CLOCK_RATE_SELECT ) ;

#elif ( CLOCK_RATE_SELECT > FREQ_DIVIDE_BY_128 )

	/* Set Double Speed Bit */
	SET_BIT( SPSR , SPSR_SPI2X ) ;
	/* Bit Masking Clock Select */
	SPCR &= ( CLOCK_MASK ) ;
	SPCR |= ( CLOCK_RATE_SELECT - 4 ) ;
#endif

	/* Enable SPI */
	SET_BIT( SPCR , SPCR_SPE ) ;

}


void SPI_voidInitSlave(void)
{

	/* SPI Peripheral Interrupt Enable */
#if   SPI_INTERRUPT ==   ENABLED
	SET_BIT( SPCR , SPCR_SPIE ) ;
#elif SPI_INTERRUPT ==   DISABLED
	CLR_BIT( SPCR , SPCR_SPIE ) ;
#endif

	/* Data Order Configuration */
#if   DATA_ORDER   ==   LSB_FIRST
	SET_BIT( SPCR , SPCR_DORD ) ;
#elif DATA_ORDER   ==   MSB_FIRST
	CLR_BIT( SPCR , SPCR_DORD ) ;
#endif

	/* Slave Initialization */
	CLR_BIT( SPCR , SPCR_MSTR ) ;

	/* Clock Polarity */
#if   CLOCK_POLARITY_MODE  ==  IDLE_HIGH
	SET_BIT( SPCR , SPCR_CPOL ) ;
#elif CLOCK_POLARITY_MODE  ==  IDLE_LOW
	CLR_BIT( SPCR , SPCR_CPOL ) ;
#endif

	/* Clock Phase */
#if   CLOCK_PHASE_MODE  ==  SETUP_FIRST
	SET_BIT( SPCR , SPCR_CPHA ) ;
#elif CLOCK_PHASE_MODE  ==  SAMPLE_FIRST
	CLR_BIT( SPCR , SPCR_CPHA ) ;
#endif

	/* Enable SPI */
	SET_BIT( SPCR , SPCR_SPE ) ;

}


u8 SPI_u8Transceive(u8 Copy_u8Data)
{
	/* Start Data Transfer */
	SPDR = Copy_u8Data ;

	/* Wait ( Busy Waiting ) Until Data Transfer is Complete */
	while( GET_BIT( SPSR , SPSR_SPIF ) == 0 ) ;

	/* Get The Exchanged Data  */
	return SPDR ;

}
