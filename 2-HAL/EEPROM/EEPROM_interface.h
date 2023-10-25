/*
 * EEPROM_interface.h
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
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

/*******************************************************/
/**** 24C08  ->  8 Kbits  -> 8192 Bits -> 1024 Byte ****/
/*******************************************************/

void EEPROM_SendDataByte( u8 Copy_u8DataByte , u16 Copy_u16ByteAddress , u8 * Copy_pu8Errors ) ;


void EEPROM_ReadDataByte( u8 * Copy_pu8DataByte , u16 Copy_u16ByteAddress , u8 * Copy_pu8Errors ) ;


#endif /* EEPROM_INTERFACE_H_ */
