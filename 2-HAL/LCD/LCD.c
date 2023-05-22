/*
 * LCD.c
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

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"LCD.h"
#include"LCD_config.h"

#include <util/delay.h>

#include"DIO_interface.h"

void LCD_voidSendCommand(u8 Copy_u8Command)
{
	//set RS pin as low for command
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_u8PIN_LOW);
	//set RW pin as low for write
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_u8PIN_LOW);
	//set command for data pin
	DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Command);
	//send enable pulse
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_u8PIN_LOW);
}

void LCD_voidSendData(u8 Copy_u8Data)
{
	//set RS pin as high for data
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,DIO_u8PIN_HIGH);
	//set RW pin as low for write
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,DIO_u8PIN_LOW);
	//set data to data pins
	DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Data);
	//send enable pulse
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT,LCD_E_PIN,DIO_u8PIN_LOW);
}

void LCD_voidInit(void)
{
	//wait more than 30 ms
	_delay_ms(40);
	//set command as 2 lines, 5*8 font size
	LCD_voidSendCommand(0b00111000);
	//set command as enable display,disable cursor,no blinking cursor
	LCD_voidSendCommand(0b00001100);
	//set command to clear display
	LCD_voidSendCommand(0b00000001);
}

void LCD_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter=0;
	while(Copy_pcString[Local_u8Counter]!= '\0')
	{
		LCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void LCD_voidGoToXY(u8 Copy_u8Xpos,u8 Copy_u8Ypos)
{
	u8 Local_u8Address;
	if(Copy_u8Xpos==0)
	{
		//position is in the first line
		Local_u8Address=Copy_u8Ypos;
	}
	else if(Copy_u8Xpos==1)
	{
		//position is in the second line
		Local_u8Address=Copy_u8Ypos+0x40;
	}
	//set 7th bit to set DDRAM address then send command
	LCD_voidSendCommand(Local_u8Address+128);
}
//4bit mode functions
void LCD4bit_voidSendCommand(u8 Copy_u8Command)
{
    // Set RS pin as low for command
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_u8PIN_LOW);

    // Set RW pin as low for write
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, DIO_u8PIN_LOW);

    // Set command for high nibble of data pins
    DIO_u8SetPortValue(LCD_DATA_PORT, (Copy_u8Command & 0xF0));

    // Send enable pulse
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_u8PIN_HIGH);
    _delay_ms(2);
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_u8PIN_LOW);

    // Set command for low nibble of data pins
    DIO_u8SetPortValue(LCD_DATA_PORT, (Copy_u8Command << 4));

    // Send enable pulse
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_u8PIN_HIGH);
    _delay_ms(2);
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_u8PIN_LOW);
}

void LCD4bit_voidSendData(u8 Copy_u8Data)
{
    // Set RS pin as high for data
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_u8PIN_HIGH);

    // Set RW pin as low for write
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, DIO_u8PIN_LOW);

    // Set data for high nibble of data pins
    DIO_u8SetPortValue(LCD_DATA_PORT, (Copy_u8Data & 0xF0));

    // Send enable pulse
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_u8PIN_HIGH);
    _delay_ms(2);
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_u8PIN_LOW);

    // Set data for low nibble of data pins
    DIO_u8SetPortValue(LCD_DATA_PORT, (Copy_u8Data << 4));

    // Send enable pulse
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_u8PIN_HIGH);
    _delay_ms(2);
    DIO_u8SetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_u8PIN_LOW);
}

void LCD4bit_voidInit(void)
{
    // Wait more than 30 ms
    _delay_ms(40);

    // Set command as 2 lines, 5*8 font size
    LCD4bit_voidSendCommand(0x28);

    // Set command as enable display, disable cursor, no blinking cursor
    LCD4bit_voidSendCommand(0x0C);

    // Set command to clear display
    LCD4bit_voidSendCommand(0x01);
}

void LCD4bit_voidSendString(const char* Copy_pcString)
{
    u8 Local_u8Counter = 0;

    while (Copy_pcString[Local_u8Counter] != '\0')
    {
        LCD4bit_voidSendData(Copy_pcString[Local_u8Counter]);
        Local_u8Counter++;
    }
}
void LCD4bit_voidGoToXY(u8 Copy_u8Xpos, u8 Copy_u8Ypos)
{
    u8 Local_u8Address;
    if (Copy_u8Xpos == 0)
    {
        // position is in the first line
        Local_u8Address = Copy_u8Ypos;
    }
    else if (Copy_u8Xpos == 1)
    {
        // position is in the second line
        Local_u8Address = Copy_u8Ypos + 0x40;
    }
    // set 7th bit to set DDRAM address then send command
    LCD4bit_voidSendCommand(Local_u8Address >> 4); // send high nibble
    LCD4bit_voidSendCommand(Local_u8Address << 4); // send low nibble
}
