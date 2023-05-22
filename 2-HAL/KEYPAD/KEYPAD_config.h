/*
 * KEYPAD_config.h
 *
 *  Created on: May 11, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:KEYPAD              */
/*      Version:1.00            */
/********************************/
/********************************/
#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/*keypad port*/
#define KEYPAD_PORT                   DIO_u8PORTB
/*rows pins*/
#define KEYPAD_ROW0                   DIO_u8PIN0
#define KEYPAD_ROW1                   DIO_u8PIN1
#define KEYPAD_ROW2                   DIO_u8PIN2
#define KEYPAD_ROW3                   DIO_u8PIN3
/*columns pins*/
#define KEYPAD_COL0                   DIO_u8PIN4
#define KEYPAD_COL1                   DIO_u8PIN5
#define KEYPAD_COL2                   DIO_u8PIN6
#define KEYPAD_COL3                   DIO_u8PIN7
/*giving default value of button if not pressed*/
#define KEYPAD_NO_BUTTON_PRESSED     0xff
/*this is the array of buttons*/
#define KEYPAD_BUTTON_ARR \
{ \
    { '7', '8', '9', '/' }, \
    { '4', '5', '6', '*' }, \
    { '1', '2', '3', '-' }, \
    { 'E', '0', '=', '+' } \
}

#endif /* KEYPAD_CONFIG_H_ */
