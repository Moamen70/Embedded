/*
 * ATmega32_Device_Header.h
 *
 * Created: 10/22/2023 12:21:34 PM
 *  Author: Moamen
 */ 


#ifndef ATMEGA32_DEVICE_HEADER_H_
#define ATMEGA32_DEVICE_HEADER_H_

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stdint.h"


/* ================================================================ */
/* ========== Base Addresses of FLASH and SRAM memories =========== */
/* ================================================================ */

#define FLASH_MEMORY		0x00
#define SRAM				0x60

/* ================================================================ */
/* ================ Bus Peripheral Base Addresses ================= */
/* ================================================================ */

#define GPIOA_Base			0x39
#define GPIOB_Base			0x36
#define GPIOC_Base			0x33
#define GPIOD_Base			0x30

#define SPI_Base			0x2D



/* ================================================================ */
/* ================= Peripheral Registers GPIO ==================== */
/* ================================================================ */

//GPIO REGISTERS====================
typedef struct {
	volatile uint8_t PIN;
	volatile uint8_t DDR;
	volatile uint8_t PORT;
}GPIO_Typedef_t;

//GPIO REGISTERS====================
typedef struct {
	volatile uint8_t SPCR;
	volatile uint8_t SPSR;
	volatile uint8_t SPDR;
}SPI_Typedef_t;

////USART REGISTERS===================
//typedef struct {
	//volatile uint8_t PIN;
	//volatile uint8_t DDR;
	//volatile uint8_t PORT;
//}USART_Typedef_t;

/* ================================================================ */
/* =================== Peripheral Instants  ======================= */
/* ================================================================ */

#define GPIOA 				((GPIO_Typedef_t *)(GPIOA_Base))
#define GPIOB  				((GPIO_Typedef_t *)(GPIOB_Base))
#define GPIOC 				((GPIO_Typedef_t *)(GPIOC_Base))
#define GPIOD 				((GPIO_Typedef_t *)(GPIOD_Base))



//////////////////////SOI///////////////////////////////////////
#define SPI 				((SPI_Typedef_t *)(SPI_Base))

////////////////////////help macros//////////////////////////
#define SET_BIT(reg,bit)		reg |=  (1<<bit)
#define CLEAR_BIT(reg,bit)		reg &= ~(1<<bit)
#define TOGGLE_BIT(reg,bit)		reg ^=  (1<<bit)
#define READ_BIT(reg,bit)		(reg>>bit) & 1

#endif /* ATMEGA32_DEVICE_HEADER_H_ */