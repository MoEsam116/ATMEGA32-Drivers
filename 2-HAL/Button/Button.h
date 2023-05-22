/*
 * Button.h
 *
 *  Created on: Apr 26, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:Button              */
/*      Version:1.00            */
/********************************/
/********************************/

#ifndef BUTTON_H_
#define BUTTON_H_

u8 Button_u8ButtonInit(u8 Copy_u8Port,u8 Copy_u8Pin);
u8 Button_u8ButtonGetValue(u8 Copy_u8Port,u8 Copy_u8Pin);

#endif /* BUTTON_H_ */
