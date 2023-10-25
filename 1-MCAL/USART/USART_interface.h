/*
 * USART_Interface.h
 *
 *  Created on: Oct 25, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:USART               */
/*      Version:1.00            */
/********************************/
/********************************/
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidInit(void);
u8 USART_u8SendCharSync(u16 Copy_u16Data);
u16 USART_u16RecieveCharSync(void);
void USART_voidSendStringSync(char * Copy_charString);
void USART_voidRecieveBufferSync(char * Copy_p8Buffer,u8 Copy_u8BufferSize);
u8 USART_u8RecieveBufferASync( char * Copy_p8Buffer,u8 Copy_u8BufferSize,void( * Copy_pvNotificationFunc)(void));

#endif /* USART_INTERFACE_H_ */
