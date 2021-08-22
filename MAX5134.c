/*******************************************************************************
*  @file      MAX5134.c 
*  @brief     Library for driving MAX5134 DAC IC using SPI.
*  @author    Negin Abbasi
*
*  Copyright (c) 2021 Negin Abbasi. All rights reserved.
********************************************************************************
* Circuit Description:
*
* MAX5134	  ---> stm32f103c8t6
* ========================================
*  (VCC) 		--> 	3.3V	
*  (GND) 		--> 	GND
*  (CS) 		--> 	PA.4  (CS Pin - chip select, enable data transfer)
*  (DIN) 		--> 	PA.7  (MOSI pin)
*  (SCLK) 	--> 	PA.5  (SCK pin)
*/


#include "MAX5134.h"
#include "stm32f1xx_hal.h"

extern SPI_HandleTypeDef hspi1;

#define MAX5134_PORT       GPIOA          // All MAX5134 lines are connected to Port A
#define MAX5134_CS         GPIO_PIN_4			// Port A.4 is CS pin

#define resetCS      HAL_GPIO_WritePin(MAX5134_PORT, MAX5134_CS , GPIO_PIN_RESET)
#define setCS        HAL_GPIO_WritePin(MAX5134_PORT, MAX5134_CS , GPIO_PIN_SET)

//************************************************************************

void max5134(void)
{				 
	  uint8_t cmd = 0x3F;        // Set control bits and Enable DAC outputs.     
	  uint8_t data1 = 255;       // Data bits
	  uint8_t data2 = 255;       // Data bits
    
    resetCS;    //Set CS to LOW to activate IC
	  HAL_SPI_Transmit(&hspi1, (uint8_t*)&cmd, 1, 1); 
	  HAL_SPI_Transmit(&hspi1, (uint8_t*)&data1, 1, 1); 
	  HAL_SPI_Transmit(&hspi1, (uint8_t*)&data2, 1, 1); 
	  setCS;
	  HAL_Delay(1);	
}  

//**********************************END************************************


