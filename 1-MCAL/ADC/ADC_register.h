/*
 * ADC_register.h
 *
 *  Created on: Jul 24, 2023
 *      Author: essam
 */
/********************************/
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:ADC                 */
/*      Version:1.00            */
/********************************/
/********************************/
#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX 		         *((volatile u8*)0x27)       //ADC multiplexer selection register
#define ADMUX_REFS0          7                           //reference selection bit 0
#define ADMUX_REFS1          6                           //reference selection bit 1
#define ADMUX_ADLRA          5                           //ADC left adjust result

#define ADCSRA 		         *((volatile u8*)0x26)       //ADC control and status register A
#define ADCSRA_ADEN          7                           //ADC enable
#define ADCSRA_ADSC          6                           //ADC conversion
#define ADCSRA_ADATE         5                           //Auto trigger
#define ADCSRA_ADIF          4                           //interrupt flag
#define ADCSRA_ADIE          3                           //interrupt enable
#define ADCSRA_ADPS2         2                           //Prescaler bit2
#define ADCSRA_ADPS1         1                           //Prescaler bit1
#define ADCSRA_ADPS0         0                           //Prescaler bit0

#define ADCH 	             *((volatile u8*)0x25)       //ADC high register
#define ADCL 		         *((volatile u8*)0x24)       //ADC low register

#endif /* ADC_REGISTER_H_ */
