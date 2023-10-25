/*
 * EEProm_program.c
 *
 *  Created on: Oct 25, 2023
 *      Author: essam
 */
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:EEPROM              */
/*      Version:1.00            */
/********************************/
/********************************/

#include"BIT_MATH.h"
#include"STD_TYPES.h"

#include"TWI_interface.h"

#include"EEPROM_config.h"
#include"EEPROM_interface.h"
#include"EEPROM_private.h"


void EEPROM_SendDataByte( u8 Copy_u8DataByte , u16 Copy_u16ByteAddress , u8 * Copy_pu8Errors )
{
	/* Master Send Start Condition */
	*( Copy_pu8Errors + 0 ) = TWI_SendStartCondition( ) ;

	/* Send 7Bits Slave Address ( 1010_A2PinConfig_2MSBinByteAddress ) + Write Request */
	*( Copy_pu8Errors + 1 ) = TWI_SendSlaveAddressWithWrite( ( ( u8 )(0x50) | ( A2_HARD_WIRED_CONNECTION << 2 ) | ( Copy_u16ByteAddress >> 8 ) ) ) ;

	/* Send the Rest of the Address ( 8 LSB in Byte Address ) */
	*( Copy_pu8Errors + 2 ) = TWI_MasterWriteDataByte( ( u8 ) Copy_u16ByteAddress ) ;

	/* Send the Data Byte to Be Written in the EEPROM */
	*( Copy_pu8Errors + 3 ) = TWI_MasterWriteDataByte( Copy_u8DataByte ) ;

	/* Send Stop Condition */
	TWI_SendStopCondition(  ) ;
}

void EEPROM_ReadDataByte( u8 * Copy_pu8DataByte , u16 Copy_u16ByteAddress , u8 * Copy_pu8Errors )
{
	/* Master Send Start Condition */
	*( Copy_pu8Errors + 0 ) = TWI_SendStartCondition( ) ;

	/* Send 7Bits Slave Address ( 1010_A2PinConfig_2MSBinByteAddress ) + Write Request to Send the Rest of the Addres in the Next Packet */
	*( Copy_pu8Errors + 1 ) = TWI_SendSlaveAddressWithWrite( ( ( u8 )(0x50) | ( A2_HARD_WIRED_CONNECTION << 2 ) | ( Copy_u16ByteAddress >> 8 ) ) ) ;

	/* Send the Rest of the Address ( 8 LSB in Byte Address ) */
	*( Copy_pu8Errors + 2 ) = TWI_MasterWriteDataByte( ( u8 ) Copy_u16ByteAddress ) ;

	/* Send Repeated Start to Change To Read Request */
	*( Copy_pu8Errors + 3 ) = TWI_SendRepeatedStart(  ) ;

	/* Send the Same 7 Bits Slave Address as Above + Read Request */
	*( Copy_pu8Errors + 4 ) = TWI_SendSlaveAddressWithRead( ( ( u8 )(0x50) | ( A2_HARD_WIRED_CONNECTION << 2 ) | ( Copy_u16ByteAddress >> 8 ) ) ) ;

	/* Read Data From EEPROM */
	*( Copy_pu8Errors + 5 ) = TWI_MasterReadDataByte( Copy_pu8DataByte ) ;

	/* Send Stop Condition */
	TWI_SendStopCondition(  ) ;

}
