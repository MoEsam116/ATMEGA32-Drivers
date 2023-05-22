/*
 * EXTI_config.h
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
#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_
/*options:
 1-LOW_LEVEL
 2-ON_CHANGE
 3-FALLING_EDGE
 4-RISING_EDGE
  */
#define INT0_SENSE           ON_CHANGE
/*options:
 1-ENABLED
 2-DISABLED
  */
#define INT0_INITIAL_STATE   ENABLED

/*options:
 1-LOW_LEVEL
 2-ON_CHANGE
 3-FALLING_EDGE
 4-RISING_EDGE
  */
#define INT1_SENSE           ON_CHANGE
/*options:
 1-ENABLED
 2-DISABLED
  */
#define INT1_INITIAL_STATE   ENABLED

/*options:
 1-FALLING_EDGE
 2-RISING_EDGE
  */
#define INT2_SENSE           RISING_EDGE
/*options:
 1-ENABLED
 2-DISABLED
  */
#define INT2_INITIAL_STATE   ENABLED

#endif /* EXTI_CONFIG_H_ */
