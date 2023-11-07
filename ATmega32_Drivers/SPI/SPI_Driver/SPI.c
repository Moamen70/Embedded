/*
 * SPI.c
 *
 * Created: 11/7/2023 4:10:40 PM
 *  Author: Moamen
 */ 

#include "SPI.h"


void MCAL_SPI_INIT(SPI_Config* SPIConfig )
{
	//Select Mode
	if (SPIConfig->SPI_Mode == Master)
	{
		SPI->SPCR |= 1<<MSTR;
	}else{
		SPI->SPCR &= ~(1<<MSTR);
	}
	// Send LSB or MSB first
	if (SPIConfig->Data_Order == LSB)
	{
		SET_BIT(SPI->SPCR,DORD);
	}else{
		CLEAR_BIT(SPI->SPCR,DORD);
	}
	//Clock Polarity
	if (SPIConfig->Clk_Polarity == HighIdle)
	{
		SET_BIT(SPI->SPCR,CPOL);
	}else{
		CLEAR_BIT(SPI->SPCR,CPOL);
	}
	//Clock Phase
	if (SPIConfig->Clk_Phase == SampleSecond)
	{
		SET_BIT(SPI->SPCR,CPHA);
	}else{
		CLEAR_BIT(SPI->SPCR,CPHA);
	}
	
	//Frequency
	SPI->SPCR |= SPIConfig->Freq;
	if (SPIConfig->Double_Speed == Double)
	{
		SET_BIT(SPI->SPSR,SPI2X);
	}else{
		CLEAR_BIT(SPI->SPSR,SPI2X);
	}
	
	
	
	//Enable SPI
	if (SPIConfig->SPI_En_Dis == Enable)
	{
		SET_BIT(SPI->SPCR,SPE);
		}else{
		CLEAR_BIT(SPI->SPCR,SPE);
	}


}

uint8_t SPI_Send_And_receive(uint8_t Data)
{
	SPI->SPDR = Data; //send data
	while(!(SPI->SPSR & (1<<SPIF)));
	return SPI->SPDR ; // Received data

}

void MCAL_SPI_SetGPIOPins(SPI_Config* SPIConfig)
{
	if (SPIConfig->SPI_Mode == Master)
	{
		GPIOB->DDR |= (1<<SS | 1<<MOSI | 1<<SCLK);
		CLEAR_BIT(GPIOB->DDR,MISO);
	}else{
		SET_BIT(GPIOB->DDR,MISO);
		GPIOB->DDR &= ~(1<<SS | 1<<MOSI | 1<<SCLK);
	}
}