/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:HAL               */
/*      SWC:SSD                 */
/*      Version:1.00            */
/********************************/
/********************************/

#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"SSD_config.h"
#include "SSD_interface.h"

static u8 SSDCath[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
static u8 SSDAnode[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void SSD_voidSSDInit(u8 Copy_u8Port)
{
	DIO_u8SetPortDirection(Copy_u8Port,DIO_u8PORT_HIGH);
}

void SSD_voidSSDDisplay(u8 Copy_u8SSDType,u8 Copy_u8Port,u8 Copy_u8Number)
{
	if(Copy_u8Number <= 9 && Copy_u8Number >=0)
	{
		if (Copy_u8SSDType==COMMON_CATHODE)
		{
			DIO_u8SetPortValue(Copy_u8Port,SSDCath[Copy_u8Number]);
		}
	}

	else if (Copy_u8SSDType== COMMON_ANODE)
	{
		DIO_u8SetPortValue(Copy_u8Port,SSDAnode[Copy_u8Number]);
	}
}

