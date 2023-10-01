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
#include <stdio.h>

#define uint32_t		unsigned int

//RCC
#define RCC_Base		0x40021000
#define RCC_APB2ENR		*(volatile uint32_t*)(RCC_Base + 0x18)
#define RCC_IOPAEN		(1<<2)

//GPIOA
#define GPIOA_BASE		0x40010800
#define GPIOA_CRL		*(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH		*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR		*(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR		*(volatile uint32_t *)(GPIOA_BASE + 0x0C)

//GPIOB
#define GPIOB_BASE		0x40010C00
#define GPIOB_CRL		*(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH		*(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR		*(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_ODR		*(volatile uint32_t *)(GPIOB_BASE + 0x0C)

void clock_init(){
	// Enable clk for GPIO A & B
	RCC_APB2ENR |= (0b11 << 2);
}

void GPIO_init(){
	GPIOA_CRL = 0;
	GPIOA_CRH = 0;
	GPIOA_ODR = 0;

	// A1 floating input
	GPIOA_CRL &= ~(0b11 << 4);
	GPIOA_CRL |=  (0b01 << 6);

	// A13 floating input
	GPIOA_CRH &= ~(0b11 << 20);
	GPIOA_CRH |=  (0b01 << 22);

	//B1 push pull output
	GPIOB_CRL |=  (0b01 << 4);
	GPIOB_CRL &= ~(0b11 << 6);

	//B13 push pull output
	GPIOB_CRH |=  (0b01 << 20);
	GPIOB_CRH |= ~(0b11 << 22);
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

		if(((GPIOA_IDR & (1 << 1)) >>1) == 0 ){

			//toggle led
			GPIOB_ODR ^= 1<<1 ;
			//single press
			while(((GPIOA_IDR & (1 << 1)) >>1) == 0 );
		}

		if(((GPIOA_IDR & (1 << 13)) >>13) == 1 ){

			//toggle led
			GPIOB_ODR ^= 1<<13 ;
		}
		wait_ms(1);

	}

	while(1);
}
