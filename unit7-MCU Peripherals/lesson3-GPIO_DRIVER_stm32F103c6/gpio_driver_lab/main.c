/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f103x8_gpio_drivers.h"
#include "STM32F103x8.h"


void clock_init(){
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
}

void GPIO_init(){
	GPIO_PinConfig_t pinConfig ;
	// pin A1 configuration
	pinConfig.GPIO_PinNumber = GPIO_PINS_1;
	pinConfig.GPIO_MODE      = GPIO_MODE_INPUT_FLO;
    MCAL_GPIO_Init(GPIOA, &pinConfig);
    // pin A13 configuration
	pinConfig.GPIO_PinNumber = GPIO_PINS_13;
	pinConfig.GPIO_MODE      = GPIO_MODE_INPUT_FLO;
    MCAL_GPIO_Init(GPIOA, &pinConfig);
    // pin B1 configuration
	pinConfig.GPIO_PinNumber 	= GPIO_PINS_1;
	pinConfig.GPIO_MODE      	= GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
    MCAL_GPIO_Init(GPIOB, &pinConfig);
    // pin B13 configuration
	pinConfig.GPIO_PinNumber 	= GPIO_PINS_13;
	pinConfig.GPIO_MODE      	= GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
    MCAL_GPIO_Init(GPIOB, &pinConfig);
}

void wait_ms(int x){
	unsigned int i ,j;
	for(i = 0 ; i < x ; i++){
		for(j = 0 ; j < 255 ; j++);
	}
}

int main(void){
	clock_init();
	GPIO_init();

	while(1){
		// PA1 connected to PU-R
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PINS_1) == GPIO_PIN_RESET)
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PINS_1);
			// single press
			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PINS_1) == GPIO_PIN_RESET);
			// PA13 connected to PU-R
		}else if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PINS_13) == GPIO_PIN_SET)
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PINS_13);
			//multi pressing
		}
		wait_ms(1);
	}

	while(1);
}
