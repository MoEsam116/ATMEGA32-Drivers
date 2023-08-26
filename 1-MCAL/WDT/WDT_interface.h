/*
 * WDT_interface.h
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
#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

void WDT_voidSleep(u8 Local_u8SleepTime);
void WDT_voidEnable(void);
void WDT_voidDisable(void);


#endif /* WDT_INTERFACE_H_ */
