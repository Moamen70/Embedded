/*
 * GPIO.c
 *
 * Created: 10/22/2023 12:26:01 PM
 *  Author: Moamen
 */ 
#include "GPIO.h"

void MCAL_GPIO_Init (GPIO_Typedef_t * GPIOx, GPIO_PinConfig_t * cfg)
{
	if (cfg->GPIO_PinMode == GPIO_MODE_OUTPUT_PP)
	{
		GPIOx->DDR |= cfg->GPIO_PinNumber;
	}
	else if(cfg->GPIO_PinMode == GPIO_MODE_INPUT_PU)
	{
		GPIOx->DDR	&= ~(cfg->GPIO_PinNumber);
		GPIOx->PORT |= cfg->GPIO_PinNumber;
	}
	else if(cfg->GPIO_PinMode == GPIO_MODE_INPUT_Hiz)
	{
		GPIOx->DDR	&= ~(cfg->GPIO_PinNumber);
		GPIOx->PORT &= ~(cfg->GPIO_PinNumber);
	}
		
}

void MCAL_GPIO_DeInit (GPIO_Typedef_t * GPIOx)
{
	GPIOx->PORT = 0x00;
	GPIOx->DDR  = 0x00;
}

 uint8_t MCAL_GPIO_ReadPin (GPIO_Typedef_t * GPIOx, uint8_t PinNumber)
 {
	 uint8_t temp = 0;
	 if ((GPIOx->PIN &= PinNumber) != 0)
	 {
		temp = GPIO_HIGH ;
	 }
	 else temp = GPIO_LOW ;
	 
	 return temp;
 }
 
 uint8_t MCAL_GPIO_ReadPort (GPIO_Typedef_t * GPIOx)
 {
	 uint8_t temp = 0;
	 temp = GPIOx->PIN;
	 return temp; 
 }
 
 void MCAL_GPIO_WritePin (GPIO_Typedef_t * GPIOx, uint8_t PinNumber, uint8_t data)
 {
	if (data)
	{
		GPIOx->PORT |= PinNumber;
	}
	else GPIOx->PORT &= ~(PinNumber);
 }
 
 void MCAL_GPIO_WritePort (GPIO_Typedef_t * GPIOx, uint8_t data)
 {
	 GPIOx->PORT = data;
 }
 
 void MCAL_GPIO_TogglePin (GPIO_Typedef_t * GPIOx, uint8_t PinNumber)
 {
	 GPIOx->PORT ^= PinNumber ;
 }
 
 
