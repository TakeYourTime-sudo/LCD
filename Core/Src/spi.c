/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI1 GPIO Configuration    
    PB3 (JTDO-TRACESWO)     ------> SPI1_SCK
    PB4 (NJTRST)     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PB3 (JTDO-TRACESWO)     ------> SPI1_SCK
    PB4 (NJTRST)     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void red_reg()
{
	/*LCD_reset;
	HAL_Delay(100);
	LCD_set;
	HAL_Delay(100);*/
	uint8_t cmd[9]={0XDB,0XDC,0X0A,0X0B,0X0C,0X0D,0X0E,0X0F};
	uint8_t rxbuf[9]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};

	CS_ON;
	CMD;
	for(int i=0;i<9;i++)
	{
		HAL_SPI_Transmit(&hspi1,&cmd[i],1,0xffff);
		HAL_SPI_Receive(&hspi1,&rxbuf[i],1,0xffff);
	}
//	HAL_SPI_Transmit(&hspi1,cmd,1,0xffff);
	//DAT;
	//HAL_SPI_Transmit(&hspi1,&cmd[1],1,0xffff);
//	HAL_SPI_Receive(&hspi1,rxbuf,1,0xffff);
	CS_OFF;
}
/*void LCD_WR_REG(uint8_t cmd){
	CS_ON;
	CMD;
	HAL_SPI_Transmit(&hspi1,&cmd,1,0xffff);
	CS_OFF;
}
void LCD_WR_DATA(uint8_t dat){
	CS_ON;
	DAT;
	HAL_SPI_Transmit(&hspi1,&dat,1,0xffff);
	CS_OFF;
}
void tftlcd(){
	LCD_reset;
		HAL_Delay(100);
		LCD_set;
		HAL_Delay(100);
		LCD_WR_REG(0XF7);
			LCD_WR_DATA(0xA9);
			LCD_WR_DATA(0x51);
			LCD_WR_DATA(0x2C);
			LCD_WR_DATA(0x82);
			LCD_WR_REG(0xC0);
			LCD_WR_DATA(0x11);
			LCD_WR_DATA(0x09);
			LCD_WR_REG(0xC1);
			LCD_WR_DATA(0x41);
			LCD_WR_REG(0XC5);
			LCD_WR_DATA(0x00);
			LCD_WR_DATA(0x0A);
			LCD_WR_DATA(0x80);
			LCD_WR_REG(0xB1);
			LCD_WR_DATA(0xB0);
			LCD_WR_DATA(0x11);
			LCD_WR_REG(0xB4);
			LCD_WR_DATA(0x02);
			LCD_WR_REG(0xB6);
			LCD_WR_DATA(0x02);
			LCD_WR_DATA(0x42);
			LCD_WR_REG(0xB7);
			LCD_WR_DATA(0xc6);
			LCD_WR_REG(0xBE);
			LCD_WR_DATA(0x00);
			LCD_WR_DATA(0x04);
			LCD_WR_REG(0xE9);
			LCD_WR_DATA(0x00);
			LCD_WR_REG(0x36);
			LCD_WR_DATA((1<<3)|(0<<7)|(1<<6)|(1<<5));
			LCD_WR_REG(0x3A);
			LCD_WR_DATA(0x66);
			LCD_WR_REG(0xE0);
			LCD_WR_DATA(0x00);
			LCD_WR_DATA(0x07);
			LCD_WR_DATA(0x10);
			LCD_WR_DATA(0x09);
			LCD_WR_DATA(0x17);
			LCD_WR_DATA(0x0B);
			LCD_WR_DATA(0x41);
			LCD_WR_DATA(0x89);
			LCD_WR_DATA(0x4B);
			LCD_WR_DATA(0x0A);
			LCD_WR_DATA(0x0C);
			LCD_WR_DATA(0x0E);
			LCD_WR_DATA(0x18);
			LCD_WR_DATA(0x1B);
			LCD_WR_DATA(0x0F);
			LCD_WR_REG(0XE1);
			LCD_WR_DATA(0x00);
			LCD_WR_DATA(0x17);
			LCD_WR_DATA(0x1A);
			LCD_WR_DATA(0x04);
			LCD_WR_DATA(0x0E);
			LCD_WR_DATA(0x06);
			LCD_WR_DATA(0x2F);
			LCD_WR_DATA(0x45);
			LCD_WR_DATA(0x43);
			LCD_WR_DATA(0x02);
			LCD_WR_DATA(0x0A);
			LCD_WR_DATA(0x09);
			LCD_WR_DATA(0x32);
			LCD_WR_DATA(0x36);
			LCD_WR_DATA(0x0F);
			LCD_WR_REG(0x11);
			HAL_Delay(120);
			LCD_WR_REG(0x29);
}*/
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
