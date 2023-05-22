/*
 * LCD.h
 *
 *  Created on: May 8, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:LCD                 */
/*      Version:1.00            */
/********************************/
/********************************/
#ifndef LCD_H_
#define LCD_H_

void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendData(u8 Copy_u8Data);
void LCD_voidInit(void);
void LCD_voidSendString(const char* Copy_pcString);
void LCD_voidGoToXY(u8 Copy_u8Xpos,u8 Copy_u8Ypos);
//4bit mode functions
void LCD4bit_voidSendCommand(u8 Copy_u8Command);
void LCD4bit_voidSendData(u8 Copy_u8Data);
void LCD4bit_voidInit(void);
void LCD4bit_voidSendString(const char* Copy_pcString);
void LCD4bit_voidGoToXY(u8 Copy_u8Xpos, u8 Copy_u8Ypos);


#endif /* LCD_H_ */
