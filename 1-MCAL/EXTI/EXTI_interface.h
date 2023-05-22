/*
 * EXTI_interface.h
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
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define LOW_LEVEL           1
#define ON_CHANGE           2
#define FALLING_EDGE        3
#define RISING_EDGE         4

#define  INT0               0
#define  INT1               1
#define  INT2               2

void EXTI_voidInt0Init(void);

void EXTI_voidInt1Init(void);

void EXTI_voidInt2Init(void);

/*Description: A function to set the required sense control of INT0 using postbuild configuration
 Inputs:Copy_u8Sense, options are:
                                  1-LOW_LEVEL
                                  2-ON_CHANGE
                                  3-FALLING_EDGE
                                  4-RISING_EDGE
Output:Error state with type u8
 */
u8 EXTI_u8INT0SenseControl(u8 Copy_u8Sense);

u8 EXTI_u8INT1SenseControl(u8 Copy_u8Sense);

u8 EXTI_u8INT2SenseControl(u8 Copy_u8Sense);

u8 EXTI_u8INTEnable(u8 Copy_u8INTNumber);

u8 EXTI_u8INTDisable(u8 Copy_u8INTNumber);

u8 EXTI_u8INT0SetCallBack(void(*Copy_pvINT0Func)(void));

u8 EXTI_u8INT1SetCallBack(void(*Copy_pvINT1Func)(void));

u8 EXTI_u8INT2SetCallBack(void(*Copy_pvINT2Func)(void));

#endif /* EXTI_INTERFACE_H_ */
