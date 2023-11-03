/*
 * stm32f103x8_uart_drivers.c
 *
 *  Created on: Nov 2, 2023
 *      Author: Moamen
 */

#include "stm32f103x8_uart_drivers.h"


/*==========================================================*/
/*Generic Variables*/
/*==========================================================*/


USART_Config_t* Global_UART_Config = NULL;

/* ==============================================================
 *              APIs Supported by "MCAL USART DRIVER"
 * ===============================================================*/


/*=================================================================
 * @Fn -                    -MCAL_UART_INIT
 * @brief -                 -Initialize the USARTx according specified parameters in USART_Config
 * @param [in] -            -USARTx : where x can be (1,2,3 depending on device used)
 * @param [in] -            -UART_Config pointer to a UART_Config structure that contains
 * @retval -                -none
 * note -                   -none
 *
================================================================= */

void MCAL_UART_INIT(USART_TypeDef* USARTx,USART_Config_t * UART_Config)
{
	uint32_t pclk ,BRR;
	Global_UART_Config = UART_Config;

	//Enable Clock For Given USART Peripheral
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
	}
	//Enable UART Module Bit 13 UE: USART enable
	USARTx->CR1 |=(1<<13);

	//Enable TX RX according to the USART_MODE configuration item
	USARTx->CR1 |= UART_Config->USART_MODE;

	//Data length
	USARTx->CR1 |= UART_Config->data_len;

	//Parity bit
	USARTx->CR1 |=UART_Config->parity;

	//Stop bits
	USARTx->CR2 |=UART_Config->stop_bits;

	//hardware flow control
	USARTx->CR3 |= UART_Config->HW_Ctrol;

	if(USARTx == USART1)
	{
		pclk = MCAL_RCC_GetPCLK2Freq() ;
	}else
	{
		pclk = MCAL_RCC_GetPCLK1Freq() ;
	}

	BRR = USART_BRR_REGISTER(pclk,UART_Config->BaudRate);
	USARTx->BRR = BRR;

	if(UART_Config->IRQ_Enable != USART_IRQ_Enable_NONE)
	{
		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_Enable;
		}else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_Enable;
		}else if(USARTx == USART3)
		{
			NVIC_IRQ39_USART3_Enable;
		}
	}
}


/*=================================================================
 * @Fn -                    -MCAL_UART_DeINIT
 * @brief -                 -Reset All USART Registers
 * @param [in] -            -USARTx : where x can be (1,2,3)
 * @retval -                -none
 * note -                   -none
================================================================= */
void MCAL_UART_DeINIT(USART_TypeDef* USARTx,USART_Config_t * UART_Config)
{
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_RESET();
		NVIC_IRQ37_USART1_Disable;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_RESET();
		NVIC_IRQ38_USART2_Disable;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_RESET();
		NVIC_IRQ39_USART3_Disable;
	}
}

/**================================================================
 * @Fn 				-	MCAL_UART_SendData
 * @brief 			-	Send Buffer With UART
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @param [in] 		- 	TxBuffer : Buffer Which holds the TX data
 * @param [in] 		- 	PollingEN : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_UART_SEND_DATA(USART_TypeDef* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn)
{
	//Wait TXE flag is set in SR
	if(PollengEn == enable)
	{
		while(USARTx->SR & 1<<7);
	}

	//Check for data length
	if(Global_UART_Config->data_len == USART_data_Length_9B)
	{
		USARTx->DR = (*pTXBuffer & (uint16_t)0x01FF);
	}else
	{
		USARTx->DR = (*pTXBuffer & (uint8_t)0xFF);
	}
}


void MCAL_UART_WAIT_TC(USART_TypeDef	* USARTx)
{
	//Wait till TC flag is set
	while(! (USARTx->SR & 1<<6) );
}

/**================================================================
 * @Fn 				-	MCAL_UART_ReceiveData
 * @brief 			-	Receive Buffer With UART
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @param [in] 		- 	RxBuffer : Buffer which holds Received data
 * @param [in] 		- 	PollingEN : Enable Polling or Disable it
 * @retval 			-	none
 * Note 			-	none
 *
 */
void MCAL_UART_RECEIVE_DATA(USART_TypeDef* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn)
{
	//Wait RXNE flag is set in SR
	if(PollengEn == enable)
	{
		while(USARTx->SR & 1<<5);
	}
	//Check for data length
	if(Global_UART_Config->data_len == USART_data_Length_9B)
	{
		if(Global_UART_Config->parity == USART_Parity_NONE)
		{
			//Read all bits and all bits are data
			*((uint16_t*)pTXBuffer) = USARTx->DR;
		}else
		{
			//Read only 8 bits becase last bit is parity
			*((uint16_t*)pTXBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}

	}else
	{
		if(Global_UART_Config->parity == USART_Parity_NONE)
		{
			//Read all bits and all bits are data
			*((uint16_t*)pTXBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}else
		{
			//Read only 7 bits becase last bit is parity
			*((uint16_t*)pTXBuffer) = (USARTx->DR & (uint8_t)0x7F);
		}
	}

}


/**================================================================
 * @Fn 				-	MCAL_UART_GPIO_Set_Pins
 * @brief 			-	Initializes GPIO Pins to be connected with the selected UART
 * @param [in] 		- 	USARTx : where x can be (1..3 depending on device used) to select USART peripheral
 * @retval 			-	none
 * Note 			-	Must open clock for AFIO & GPIO After GPIO Initialization
 *
 */
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef* USARTx)
{
	GPIO_PinConfig_t pinConfig ;

	if(USARTx == USART1)
	{
		//PA9  TX
		pinConfig.GPIO_PinNumber = GPIO_PINS_9;
		pinConfig.GPIO_MODE	= GPIO_MODE_OUTPUT_AF_PP;
		pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pinConfig);

		//PA10 RX
		pinConfig.GPIO_PinNumber = GPIO_PINS_10;
		pinConfig.GPIO_MODE	= GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &pinConfig);

		//PA11 CTS
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			pinConfig.GPIO_PinNumber = GPIO_PINS_11;
			pinConfig.GPIO_MODE	= GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinConfig);

		}

		//PA12 RTS
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_RTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			pinConfig.GPIO_PinNumber = GPIO_PINS_12;
			pinConfig.GPIO_MODE	= GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);

		}
	}

	if(USARTx == USART2)
	{
		//PA2  TX
		pinConfig.GPIO_PinNumber = GPIO_PINS_2;
		pinConfig.GPIO_MODE	= GPIO_MODE_OUTPUT_AF_PP;
		pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pinConfig);

		//PA3 RX
		pinConfig.GPIO_PinNumber = GPIO_PINS_3;
		pinConfig.GPIO_MODE	= GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &pinConfig);

		//PA0 CTS
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			pinConfig.GPIO_PinNumber = GPIO_PINS_0;
			pinConfig.GPIO_MODE	= GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinConfig);

		}

		//PA1 RTS
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_RTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			pinConfig.GPIO_PinNumber = GPIO_PINS_1;
			pinConfig.GPIO_MODE	= GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);

		}
	}

	if(USARTx == USART3)
	{
		//PB10  TX
		pinConfig.GPIO_PinNumber = GPIO_PINS_10;
		pinConfig.GPIO_MODE	= GPIO_MODE_OUTPUT_AF_PP;
		pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinConfig);

		//PB11 RX
		pinConfig.GPIO_PinNumber = GPIO_PINS_11;
		pinConfig.GPIO_MODE	= GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOB, &pinConfig);

		//PB13 CTS
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			pinConfig.GPIO_PinNumber = GPIO_PINS_13;
			pinConfig.GPIO_MODE	= GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &pinConfig);

		}

		//PB14 RTS
		if(Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_RTS || Global_UART_Config->HW_Ctrol == USART_HW_FlowCtrl_CTS_RTS)
		{
			pinConfig.GPIO_PinNumber = GPIO_PINS_14;
			pinConfig.GPIO_MODE	= GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinConfig);

		}
	}
}

//ISR

void USART1_IRQHandler(void)
{
	Global_UART_Config->p_IRQ_call_back();
}

void USART2_IRQHandler(void)
{
	Global_UART_Config->p_IRQ_call_back();

}

void USART3_IRQHandler(void)
{
	Global_UART_Config->p_IRQ_call_back();

}



