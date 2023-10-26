/*
 * stm32F103x8_exti_drivers.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Moamen
 */

#include "stm32f103x8_exti_drivers.h"
#include "stm32f103x8_gpio_drivers.h"


//Generic Variables========================
 void (* GP_IRQ_CallBack[15])(void);

//Generic Macros========================

#define AFIO_GPIO_EXTI_Mapping(x)		(	(x==GPIOA)?0:\
											(x==GPIOB)?1:\
											(x==GPIOC)?2:\
											(x==GPIOD)?3:0 )


#define Enable_NVIC(x)				(	(x==0)?NVIC_IRQ6_EXTI0_Enable:\
										(x==1)?NVIC_IRQ7_EXTI1_Enable:\
										(x==2)?NVIC_IRQ8_EXTI2_Enable:\
										(x==3)?NVIC_IRQ9_EXTI3_Enable:\
										(x==4)?NVIC_IRQ10_EXTI4_Enable:\
										(x==5||x==6||x==7||x==8||x==9)?NVIC_IRQ23_EXTI5_9_Enable:\
										(x==10||x==11||x==12||x==13||x==14)?NVIC_IRQ40_EXTI10_15_Enable:0 )

#define Disable_NVIC(x)				(	(x==0)?NVIC_IRQ6_EXTI0_Disable:\
										(x==1)?NVIC_IRQ7_EXTI1_Disable:\
										(x==2)?NVIC_IRQ8_EXTI2_Disable:\
										(x==3)?NVIC_IRQ9_EXTI3_Disable:\
										(x==4)?NVIC_IRQ10_EXTI4_Disable:\
										(x==5||x==6||x==7||x==8||x==9)?NVIC_IRQ23_EXTI5_9_Disable:\
										(x==10||x==11||x==12||x==13||x==14)?NVIC_IRQ40_EXTI10_15_Disable:0 )


//Generic Functions========================

void Update_EXTI(EXTI_PinConfig_t* EXTI_Config)
{
	//1- Configure GPIO to be AF input -> floating input
	GPIO_PinConfig_t pinConfig;
	pinConfig.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_Pin;
	pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_Port, &pinConfig);

	// Update AFIO to route input to EXTI
	uint8_t AFIO_EXTI_index   = EXTI_Config->EXTI_PIN.EXTI_InputLineNumber / 4;

	uint8_t AFIO_EXTI_postion = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber % 4) * 4;

	//Clear the 4 bits
	AFIO->EXTICR[AFIO_EXTI_index] &= ~(0xF << AFIO_EXTI_postion);
	//set the choosen 4 bits based on EXTI line and GPIO Port
	AFIO->EXTICR[AFIO_EXTI_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port) & 0xF) <<AFIO_EXTI_postion );

	//3- Update Rising Falling Reg
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	if(EXTI_Config->Trigger_Case == EXTI_Trigger_Rising)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_Falling)
	{
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}

	//4- IRQ Handling Callback
	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;

	//5- Enable mask Reg
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1 <<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber );
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}else if(EXTI_Config->IRQ_EN == EXTI_IRQ_Disable)
	{
		EXTI->IMR &= ~(1 <<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber );
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}

}






/**================================================================
 * @Fn-MCAL_EXTI_GPIO_Init
 * @brief -Initialize EXTI according to parameters in EXTI_PinConfig_t
 * @param [in] -EXTI_Config: has all information to map Pins to its EXTI Lines
 * @retval -None
 * Note-
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

/**================================================================
 * @Fn-MCAL_EXTI_GPIO_DeInit
 * @brief -Rsest EXTI
 * @param [in] -None
 * @retval -None
 * Note-
 */
void MCAL_EXTI_GPIO_DeInit(Void)
{
	EXTI->EMR = 0x00000000;
	EXTI->IMR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->SWIER = 0x00000000;
	// Write 1 to clear interrupt
	EXTI->PR = 0xFFFFFFFF;

	//Disable EXTI IRQ From NVIC
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ40_EXTI10_15_Disable;
	NVIC_IRQ23_EXTI5_9_Disable;
	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
}

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

//============================================================================
//=================================ISR Functions==============================
//============================================================================

void EXTI0_IRQHandler(void)
{
	// clear bit of PR reg (interrupt flag)
	EXTI->PR |= (1 << 0);

	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler(void)
{
	// clear bit of PR reg (interrupt flag)
	EXTI->PR |= (1 << 1);

	GP_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler(void)
{
	// clear bit of PR reg (interrupt flag)
	EXTI->PR |= (1 << 2);

	GP_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler(void)
{
	// clear bit of PR reg (interrupt flag)
	EXTI->PR |= (1 << 3);

	GP_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler(void)
{
	// clear bit of PR reg (interrupt flag)
	EXTI->PR |= (1 << 4);

	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5) { EXTI->PR |= (1 << 5)	; GP_IRQ_CallBack[5]() ; }
	if(EXTI->PR & 1<<6) { EXTI->PR |= (1 << 6)	; GP_IRQ_CallBack[6]() ; }
	if(EXTI->PR & 1<<7) { EXTI->PR |= (1 << 7)	; GP_IRQ_CallBack[7]() ; }
	if(EXTI->PR & 1<<8) { EXTI->PR |= (1 << 8)	; GP_IRQ_CallBack[8]() ; }
	if(EXTI->PR & 1<<9) { EXTI->PR |= (1 << 9)	; GP_IRQ_CallBack[9]() ; }

}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1<<10) { EXTI->PR |= (1 << 10)	; GP_IRQ_CallBack[10]() ; }
	if(EXTI->PR & 1<<11) { EXTI->PR |= (1 << 11)	; GP_IRQ_CallBack[11]() ; }
	if(EXTI->PR & 1<<12) { EXTI->PR |= (1 << 12)	; GP_IRQ_CallBack[12]() ; }
	if(EXTI->PR & 1<<13) { EXTI->PR |= (1 << 13)	; GP_IRQ_CallBack[13]() ; }
	if(EXTI->PR & 1<<14) { EXTI->PR |= (1 << 14)	; GP_IRQ_CallBack[14]() ; }
	if(EXTI->PR & 1<<15) { EXTI->PR |= (1 << 15)	; GP_IRQ_CallBack[15]() ; }
}
