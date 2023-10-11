/*
 * stm32f103x8_gpio_drivers.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Moamen
 */

#ifndef INC_STM32F103X8_GPIO_DRIVERS_H_
#define INC_STM32F103X8_GPIO_DRIVERS_H_

#include "STM32F103x8.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------
// Config structure
typedef struct{
	uint16_t GPIO_PinNumber; 	// Specify the pin number
	// Can be value of @ref GPIO_PINS_define

	uint8_t GPIO_MODE; 		// Specify the pin mode I/O
	// Can be value of @ref GPIO_MODE_define

	uint8_t GPIO_Output_Speed; 	// Specify the pin speed (output only)
	// Can be value of @ref GPIO_SPEED_define

}GPIO_PinConfig_t;


/*@ref Module_REF_NAME_define===========================
 */

//GPIO_PIN_state
#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET		0



//GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_Enabled		1
#define GPIO_RETURN_LOCK_Erorr			0




//GPIO_PINS_define
#define GPIO_PINS_0		((uint16_t)0x0001)
#define GPIO_PINS_1		((uint16_t)0x0002)
#define GPIO_PINS_2		((uint16_t)0x0004)
#define GPIO_PINS_3		((uint16_t)0x0008)
#define GPIO_PINS_4		((uint16_t)0x0010)
#define GPIO_PINS_5		((uint16_t)0x0020)
#define GPIO_PINS_6		((uint16_t)0x0040)
#define GPIO_PINS_7		((uint16_t)0x0080)
#define GPIO_PINS_8		((uint16_t)0x0100)
#define GPIO_PINS_9		((uint16_t)0x0200)
#define GPIO_PINS_10	((uint16_t)0x0400)
#define GPIO_PINS_11	((uint16_t)0x0800)
#define GPIO_PINS_12	((uint16_t)0x1000)
#define GPIO_PINS_13	((uint16_t)0x2000)
#define GPIO_PINS_14	((uint16_t)0x4000)
#define GPIO_PINS_15	((uint16_t)0x8000)
#define GPIO_PINS_ALL	((uint16_t)0xFFFF)



//GPIO_MODE_define
#define GPIO_MODE_ANALOG				0x0u //Analog
#define GPIO_MODE_INPUT_FLO				0x1u //Input Floating
#define GPIO_MODE_INPUT_PU				0x2u //Input Pull Up
#define GPIO_MODE_INPUT_PD				0x3u //Input Pull Down
#define GPIO_MODE_OUTPUT_PP				0x4u //Output push pull
#define GPIO_MODE_OUTPUT_OD				0x5u //Output open drain
#define GPIO_MODE_OUTPUT_AF_PP			0x6u //Output push pull alternative
#define GPIO_MODE_OUTPUT_AF_OD			0x7u //Output open drain alternative
#define GPIO_MODE_INPUT_AF				0x8u //Input alternative


//GPIO_SPEED_define
#define GPIO_SPEED_10M			0x1u; //Output mode, max speed 10 MHz
#define GPIO_SPEED_2M			0x2u; //Output mode, max speed 2 MHz
#define GPIO_SPEED_50M			0x3u; //Output mode, max speed 50 MHz


/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */

void MCAL_GPIO_Init(GPIO_TypeDef * GPIOX , GPIO_PinConfig_t * PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOX);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOX , uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOX );

void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOX , uint16_t PinNumber , uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOX , uint16_t value );

void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOX , uint16_t PinNumber);


uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOX , uint16_t PinNumber);


#endif /* INC_STM32F103X8_GPIO_DRIVERS_H_ */
