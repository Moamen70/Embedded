/*
 * stm32f103x8_spi_drivers.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Moamen
 */

#include "stm32f103x8_spi_drivers.h"

/*=================================================================
 *                     Generic Variables
 *=================================================================
 */
SPI_Config_t* G_SPI_Config[2]={NULL,NULL};


/*=================================================================
 *                     Generic Macros
 *=================================================================
 */
#define SPI1_INDEX               0
#define SPI2_INDEX               1

#define SPI_SR_TXE               1<<1
#define SPI_SR_RXNE              1<<0

/*=================================================================
 *                     APIs
 *=================================================================
 */


/**=================================================================
 * @Fn -                    -MCAL_SPI_INIT
 * @brief -                 -INIT SPI Protocol Registers according SPI_Config_t
 * @param [in] -            -SPIx : where x can be (1..2 depending on device used)
 * @param [in] -            -SPI_Config : This is configuration which user will pass it
 * @retval -                -none
 * note -                   -Support for SPI Full Dublex Master/Slave Only & NSS HW/SW
 */
/**================================================================= */

void MCAL_SPI_INIT(SPI_TypeDef* SPIx,SPI_Config_t* SPI_Config)
{
	uint16_t tmep_CR1 = 0;
	uint16_t tmep_CR2 = 0;

	if(SPIx == SPI1)
	{
		G_SPI_Config[SPI1_INDEX] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}else
	{
		G_SPI_Config[SPI2_INDEX] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}

	//Set Bit 6 SPE: SPI enable
	tmep_CR1 |=(1<<6);
	// Master or Slave
	tmep_CR1 |= SPI_Config->Device_mode;

	tmep_CR1 |= SPI_Config->comunication_mode;

	tmep_CR1 |= SPI_Config->frame_format;

	tmep_CR1 |= SPI_Config->data_size;

	tmep_CR1 |= SPI_Config->CLK_Polarity;

	tmep_CR1 |= SPI_Config->CLK_Phase;

	tmep_CR1 |= SPI_Config->Bound_rate_pres;

	if(SPI_Config->Nss == SPI_NSS_Hard_Master_Output_EN)
	{
		tmep_CR2 |=SPI_Config->Nss;
	}
	else if (SPI_Config->Nss == SPI_NSS_Hard_Master_Output_DIS) {
		tmep_CR2 &=SPI_Config->Nss;
	}
	else {
		tmep_CR1 |=SPI_Config->Nss;
	}

	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		tmep_CR2 |=SPI_Config->IRQ_Enable;
		if(SPIx==SPI1)
		{
			NVIC_IRQ35_SPI1_Enable;
		}
		else if (SPIx==SPI2) {
			NVIC_IRQ36_SPI2_Enable;
		}
	}

	SPIx->CR1 = (uint32_t)tmep_CR1;
	SPIx->CR2 = (uint32_t)tmep_CR2;
}

void MCAL_SPI_DeINIT(SPI_TypeDef* SPIx)
{
	if(SPIx == SPI1)
	{
		RCC_SPI1_CLK_RESET();
		NVIC_IRQ35_SPI1_Disable;
	}else
	{
		RCC_SPI2_CLK_RESET();
		NVIC_IRQ36_SPI2_Disable;
	}
}

void MCAL_SPI_SEND_DATA(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn)
{
	//todo recive only
	if(PollingEn == Enable)
	{
		while(!(SPIx->SR & SPI_SR_TXE));
	}
	SPIx->DR = *pTxBuffer;
}


void MCAL_SPI_RECEIVE_DATA(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn)
{
	if(PollingEn == Enable)
	{
		while(!(SPIx->SR & SPI_SR_RXNE));
	}
	*pTxBuffer = SPIx->DR;
}

void MCAL_SPI_TX_RX(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn)
{
	MCAL_SPI_SEND_DATA(SPIx, pTxBuffer, PollingEn);
	MCAL_SPI_RECEIVE_DATA(SPIx, pTxBuffer, PollingEn);
}

void MCAL_SPI_GPIO_SET_PINS(SPI_TypeDef* SPIx)
{
	GPIO_PinConfig_t pinConfig;
	//	Alternate function
	//	SPI1_NSS PA4
	//	SPI1_SCK PA5
	//	SPI1_MISO PA6
	//	SPI1_MOSI PA7
	if(SPIx == SPI1)
	{
		if(G_SPI_Config[SPI1_INDEX]->Device_mode == SPI_Device_Master)
		{
			switch(G_SPI_Config[SPI1_INDEX]->Nss)
			{
			case SPI_NSS_Hard_Master_Output_EN :
				pinConfig.GPIO_PinNumber = GPIO_PINS_4;
				pinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;

				MCAL_GPIO_Init(GPIOA, &pinConfig);
				break;
			case SPI_NSS_Hard_Master_Output_DIS :
				pinConfig.GPIO_PinNumber = GPIO_PINS_4;
				pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

				MCAL_GPIO_Init(GPIOA, &pinConfig);
				break;
			}
			//	SPI1_SCK PA5
			pinConfig.GPIO_PinNumber = GPIO_PINS_5;
			pinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;

			MCAL_GPIO_Init(GPIOA, &pinConfig);

			//	SPI1_MISO PA6
			pinConfig.GPIO_PinNumber = GPIO_PINS_6;
			pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

			MCAL_GPIO_Init(GPIOA, &pinConfig);

			//	SPI1_MOSI PA7
			pinConfig.GPIO_PinNumber = GPIO_PINS_7;
			pinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;

			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}
		//Slave
		else
		{
			if(G_SPI_Config[SPI1_INDEX]->Nss == SPI_NSS_Hard_slave)
			{
				pinConfig.GPIO_PinNumber = GPIO_PINS_4;
				pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

				MCAL_GPIO_Init(GPIOA, &pinConfig);
			}

			//	SPI1_SCK PA5
			pinConfig.GPIO_PinNumber = GPIO_PINS_5;
			pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

			MCAL_GPIO_Init(GPIOA, &pinConfig);

			//	SPI1_MISO PA6
			pinConfig.GPIO_PinNumber = GPIO_PINS_6;
			pinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;

			MCAL_GPIO_Init(GPIOA, &pinConfig);

			//	SPI1_MOSI PA7
			pinConfig.GPIO_PinNumber = GPIO_PINS_7;
			pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}
		///////////////////////////////////////////////////////////////////////////////////////
	//SPI2
	}else
	{
		if(G_SPI_Config[SPI2_INDEX]->Device_mode == SPI_Device_Master)
				{
					switch(G_SPI_Config[SPI2_INDEX]->Nss)
					{
					case SPI_NSS_Hard_Master_Output_EN :
						pinConfig.GPIO_PinNumber = GPIO_PINS_12;
						pinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
						pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;

						MCAL_GPIO_Init(GPIOB, &pinConfig);
						break;
					case SPI_NSS_Hard_Master_Output_DIS :
						pinConfig.GPIO_PinNumber = GPIO_PINS_12;
						pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

						MCAL_GPIO_Init(GPIOB, &pinConfig);
						break;
					}
					//	SPI1_SCK PB13
					pinConfig.GPIO_PinNumber = GPIO_PINS_13;
					pinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
					pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;

					MCAL_GPIO_Init(GPIOB, &pinConfig);

					//	SPI1_MISO PB14
					pinConfig.GPIO_PinNumber = GPIO_PINS_14;
					pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

					MCAL_GPIO_Init(GPIOB, &pinConfig);

					//	SPI1_MOSI PB15
					pinConfig.GPIO_PinNumber = GPIO_PINS_15;
					pinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
					pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;

					MCAL_GPIO_Init(GPIOB, &pinConfig);
				}
				//Slave
				else
				{
					if(G_SPI_Config[SPI2_INDEX]->Nss == SPI_NSS_Hard_slave)
					{
						pinConfig.GPIO_PinNumber = GPIO_PINS_12;
						pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

						MCAL_GPIO_Init(GPIOB, &pinConfig);
					}

					//	SPI1_SCK PB13
					pinConfig.GPIO_PinNumber = GPIO_PINS_13;
					pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

					MCAL_GPIO_Init(GPIOB, &pinConfig);

					//	SPI1_MISO PB14
					pinConfig.GPIO_PinNumber = GPIO_PINS_14;
					pinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
					pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;

					MCAL_GPIO_Init(GPIOB, &pinConfig);

					//	SPI1_MOSI PB15
					pinConfig.GPIO_PinNumber = GPIO_PINS_15;
					pinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;

					MCAL_GPIO_Init(GPIOB, &pinConfig);
				}
	}
}


//ISR
void SPI1_IRQHandler(void)
{

	struct s_IRQ_SCR irq_src;

	irq_src.TXE = ((SPI1->SR & 1<<1) >> 1);
	irq_src.RXNT = ((SPI1->SR & 1<<0) >> 0);
	irq_src.ERR = ((SPI1->SR & 1<<4) >> 4);

	G_SPI_Config[SPI1_INDEX]->p_IRQ(irq_src);
}

void SPI2_IRQHandler(void)
{
	struct s_IRQ_SCR irq_src;

	irq_src.TXE = ((SPI2->SR & 1<<1) >> 1);
	irq_src.RXNT = ((SPI2->SR & 1<<0) >> 0);
	irq_src.ERR = ((SPI2->SR & 1<<4) >> 4);

	G_SPI_Config[SPI2_INDEX]->p_IRQ(irq_src);
}

