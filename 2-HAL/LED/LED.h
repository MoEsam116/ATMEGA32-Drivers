/*
 * LED.h
 *
 *  Created on: Apr 27, 2023
 *      Author: essam
 */
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:LED                 */
/*      Version:1.00            */
/********************************/
/********************************/
#ifndef LED_H_
#define LED_H_

#define SRC 1
#define SINK 0

u8 LED_u8LedOn(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Connection);
u8 LED_u8LedOff(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Connection);


#endif /* LED_H_ */
