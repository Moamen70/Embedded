/*
 * stm32f103x8_gpio_drivers.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Moamen
 */

#include "stm32f103x8_gpio_drivers.h"

uint8_t Get_CRLH_Position(uint16_t pinNumber)
{
	switch(pinNumber)
	{
	case GPIO_PINS_0 :
		return 0;
		break;
	case GPIO_PINS_1 :
		return 4;
		break;
	case GPIO_PINS_2 :
		return 8;
		break;
	case GPIO_PINS_3 :
		return 12;
		break;
	case GPIO_PINS_4 :
		return 16;
		break;
	case GPIO_PINS_5 :
		return 20;
		break;
	case GPIO_PINS_6 :
		return 24;
		break;
	case GPIO_PINS_7 :
		return 28;
		break;
	case GPIO_PINS_8 :
		return 0;
		break;
	case GPIO_PINS_9 :
		return 4;
		break;
	case GPIO_PINS_10 :
		return 8;
		break;
	case GPIO_PINS_11 :
		return 12;
		break;
	case GPIO_PINS_12 :
		return 16;
		break;
	case GPIO_PINS_13 :
		return 20;
		break;
	case GPIO_PINS_14 :
		return 24;
		break;
	case GPIO_PINS_15 :
		return 28;
		break;
	}
	return 0;
}
/**================================================================
 * @Fn-MCAL_GPIO_Init
 * @brief -Initialize GPIOx Piny according to parameters in PinConfig
 * @param [in] -GPIOx: x can be (A:D) to select which GPIO to initialize
 * @param [in] -Piny: y can be (0:15) to select configuration of pin
 * @retval -None
 * Note-
 */
void MCAL_GPIO_Init(GPIO_TypeDef * GPIOX , GPIO_PinConfig_t * PinConfig){
	//Port configuration reg low pin (0:7)
	//Port configuration reg high pin (8:15)
	uint32_t* configRegister = NULL;
	// variable to store the 4 configuration bits
	uint8_t pin_config = 0;
	// pointer to CRL or CRH according to pin number
	configRegister = (PinConfig->GPIO_PinNumber < GPIO_PINS_8)? &GPIOX->CRL : &GPIOX->CRH;
	// make the MOD & CNF bits = 00 00 for the chosen bin
	// check the mode of the pin
	if(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD  ||
			PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP ||
			PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD    ||
			PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP)
	{	//Write the CNF & MOD bits for output mode
		pin_config = ((PinConfig->GPIO_MODE - 4) << 2 | PinConfig->GPIO_Output_Speed) & 0x0F;
	}else
	{
		if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO  || PinConfig->GPIO_MODE == GPIO_MODE_ANALOG)
		{	//Write the CNF & MOD bits for input mode (floating or analog)
			pin_config = (((PinConfig->GPIO_MODE ) << 2) | 0x0 ) & 0x0F;

		}else if (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU || PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PD)
		{	//Write the CNF & MOD bits for input mode (PU or PD)
			pin_config = (((GPIO_MODE_INPUT_PU ) << 2) | 0x0 ) & 0x0F;
			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PD)
			{	// clear ODR bit to choose PD input mode
				GPIOX->ODR  &= ~(PinConfig->GPIO_PinNumber);
			}else
			{	// Set ODR bit to choose PU input mode
				GPIOX->ODR  |=  (PinConfig->GPIO_PinNumber);
			}
		}
		else if (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_AF)
		{	////Write the CNF & MOD bits for input alternative mode (same as floating)
			pin_config = (((GPIO_MODE_INPUT_FLO ) << 2) | 0x0 ) & 0x0F;
		}

	}
	// Write on CRL or CRH registers
	(*configRegister) |= (pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
}



/**================================================================
 * @Fn-MCAL_GPIO_DeInit
 * @brief -Reset GPIOx to defult value
 * @param [in] -GPIOx: x can be (A:D) to select which GPIO to get reset
 * @retval -None
 * Note-
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOX){
	if(GPIOX == GPIOA){
		RCC->APB2RSTR |=  (1 << 2);
		RCC->APB2RSTR &= ~(1 << 2);
	}else if(GPIOX == GPIOB)
	{
		RCC->APB2RSTR |=  (1 << 3);
		RCC->APB2RSTR &= ~(1 << 3);
	}else if(GPIOX == GPIOC)
	{
		RCC->APB2RSTR |=  (1 << 4);
		RCC->APB2RSTR &= ~(1 << 4);
	}else if(GPIOX == GPIOD)
	{
		RCC->APB2RSTR |=  (1 << 5);
		RCC->APB2RSTR &= ~(1 << 5);
	}
}

/**================================================================
 * @Fn-MCAL_GPIO_ReadPin
 * @brief -Read the value of the specific pin on specific gpio
 * @param [in] -GPIOX: X can be (A:D) to select which GPIO to read from
 * @param [in] -PinNumber: Can be (0:15) to select which pin to read from
 * @retval -The value on the pin
 * Note-
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOX , uint16_t PinNumber)
{
	uint8_t bitStatus;
	if((GPIOX->IDR & PinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		bitStatus = GPIO_PIN_SET;
	}else
	{
		bitStatus = GPIO_PIN_RESET;
	}
	return bitStatus;
}


/**================================================================
 * @Fn-MCAL_GPIO_ReadPort
 * @brief -Read the value of the specific gpio port
 * @param [in] -GPIOX: X can be (A:D) to select which GPIO to read from
 * @retval -The value on the port
 * Note-
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOX )
{
	return (uint16_t)GPIOX->IDR  ;
}


/**================================================================
 * @Fn-MCAL_GPIO_WritePin
 * @brief -Write a value on a specific pin on specific gpio
 * @param [in] -GPIOX: X can be (A:D) to select which GPIO to write on
 * @param [in] -PinNumber: Can be (0:15) to select which pin to write on
 * @param [in] -value: To select the value written on pin
 * @retval -None
 * Note-
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOX , uint16_t PinNumber , uint8_t value)
{
	if (value == GPIO_PIN_SET)
	{
		(GPIOX->BSRR = (uint32_t)(PinNumber)) ;
	}else
	{
		(GPIOX->BRR = (uint32_t)(PinNumber)) ;
	}
}


/**================================================================
 * @Fn-MCAL_GPIO_WritePort
 * @brief -Write a value on a specific gpio
 * @param [in] -GPIOX: X can be (A:D) to select which GPIO to write on
 * @param [in] -value: To select the value written on port
 * @retval -None
 * Note-
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOX , uint16_t value )
{
	GPIOX->ODR &= (uint32_t)value ;
}


/**================================================================
 * @Fn-MCAL_GPIO_TogglePin
 * @brief -Toggle specific pin on a specific gpio
 * @param [in] -GPIOX: X can be (A:D) to select which GPIO has the pin need to toggle
 * @param [in] -PinNumber: Can be (0:15) to select which pin to get toggled
 * @retval -None
 * Note-
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOX , uint16_t PinNumber)
{
	GPIOX->ODR ^= (PinNumber);
}


/**================================================================
 * @Fn-MCAL_GPIO_LockPin
 * @brief -Toggle specific pin on a specific gpio
 * @param [in] -GPIOX: X can be (A:D) to select which GPIO has the pin need to get locked
 * @param [in] -PinNumber: Can be (0:15) to select which pin to get locked
 * @retval -None
 * Note-
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOX , uint16_t PinNumber)
{
	volatile uint32_t temp;

	GPIOX->LCKR |= (1 << 16);
	GPIOX->LCKR |= PinNumber;

	GPIOX->LCKR |=  (1 << 16);
	GPIOX->LCKR &= ~(1 << 16);
	GPIOX->LCKR |=  (1 << 16);

	temp = GPIOX->LCKR;

	if((GPIOX->LCKR) & (1 << 16))
	{
		return GPIO_RETURN_LOCK_Enabled;
	}else
	{
		return GPIO_RETURN_LOCK_Erorr;
	}

}




