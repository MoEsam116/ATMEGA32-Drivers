/*
 * WDT_register.h
 *
 *  Created on: Aug 26, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:WDT                 */
/*      Version:1.00            */
/********************************/
/********************************/
#ifndef WDT_REGISTER_H_
#define WDT_REGISTER_H_

#define WDTCR            *((volatile u8*)0x41)

#define WDTCR_WDTOE                4
#define WDTCR_WDE                  3
#define WDTCR_WDP2                 2
#define WDTCR_WDP1                 1
#define WDTCR_WDP0                 0

#endif /* WDT_REGISTER_H_ */
