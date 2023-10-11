/*
 * STM32F103x8.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Moamen
 */

#ifndef INC_STM32F103X8_H_
#define INC_STM32F103X8_H_


//-----------------------------
//Includes
//-----------------------------
#include <stdio.h>
#include <stdint.h>
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BASE		0X08000000
#define SYSTEM_MEMORY_BASE		0X1FFFF000
#define SRAM_BASE				0X20000000

#define Peripheral_BASE			0x40000000



//-----------------------------
//Base addresses for BUS Peripherals
//-----------------------------

// Base address for APB2 bus peripherals
#define GPIOA_BASE			0x40010800
#define GPIOB_BASE			0x40010C00
#define GPIOC_BASE			0x40011000
#define GPIOD_BASE			0x40011400

#define EXTI_BASE			0x40010400

#define AFIO_BASE			0x40010000

// Base address for AHB bus peripherals
#define RCC_BASE			0x40021000

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//GPIO REGISTERS====================
typedef struct {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;


//EXTI REGISTERS=========================

typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;

//AFIO REGISTERS======================

typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	uint32_t RESERVED;
	volatile uint32_t MAPR2;
}AFIO_TypeDef;


//RCC REGISTERS======================

typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA		((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB		((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC		((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD		((GPIO_TypeDef *) GPIOD_BASE)

#define RCC			((RCC_TypeDef *) RCC_BASE)

#define EXTI		((EXTI_TypeDef *) EXTI_BASE)

#define AFIO		((AFIO_TypeDef *) AFIO_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()		(RCC->APB2ENR |= (1<<2))
#define RCC_GPIOB_CLK_EN()		(RCC->APB2ENR |= (1<<3))
#define RCC_GPIOC_CLK_EN()		(RCC->APB2ENR |= (1<<4))
#define RCC_GPIOD_CLK_EN()		(RCC->APB2ENR |= (1<<5))

#define RCC_AFIO_CLK_EN()		(RCC->APB2ENR |= (1<<0))

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*




#endif /* INC_STM32F103X8_H_ */
