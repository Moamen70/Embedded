/*
 * stm32f103x8_rcc_drivers.h
 *
 *  Created on: Nov 2, 2023
 *      Author: Moamen
 */

#ifndef INC_STM32F103X8_RCC_DRIVERS_H_
#define INC_STM32F103X8_RCC_DRIVERS_H_

#include "STM32F103x8.h"
#include "stm32f103x8_gpio_drivers.h"

#define HSI_CLK      (uint32_t)8000000
#define HSE_CLK      (uint32_t)16000000

uint32_t MCAL_RCC_GetSYSCLKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLKFreq(void);

#endif /* INC_STM32F103X8_RCC_DRIVERS_H_ */
