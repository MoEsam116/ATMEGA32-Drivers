/*
 * SPI_inerface.h
 *
 *  Created on: Oct 25, 2023
 *      Author: essam
 */
/********************************/
/*      Author:Mohamed Esam     */
/*      Layer:MCAL              */
/*      SWC:SPI                 */
/*      Version:1.00            */
/********************************/
/********************************/
#ifndef SPI_INERFACE_H_
#define SPI_INERFACE_H_

void SPI_voidInitMaster(void);
void SPI_voidInitSlave( void ) ;
u8 SPI_u8Transceive(u8 Copy_u8Data);

#endif /* SPI_INERFACE_H_ */
