/*
 * SPI.h
 *
 * Created: 11/7/2023 4:10:51 PM
 *  Author: Moamen
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "ATmega32_Device_Header.h"

enum SPI_EnableDisable 
{
	Disable,
	Enable
};

enum Mode
{
	Slave,
	Master
};
	
enum DataOrder
{
	MSB,
	LSB
};

enum ClkPolarity
{
	LowIdle,
	HighIdle	
};

enum ClkPhase
{
	SampleFirst,
	SampleSecond
};

enum DoubleSpeed
{
	Normal,
	Double
};





typedef struct {
	enum SPI_EnableDisable	SPI_En_Dis;		
	enum Mode				SPI_Mode;
	enum DataOrder			Data_Order;
	enum ClkPolarity		Clk_Polarity;
	enum ClkPhase			Clk_Phase;
	uint8_t Freq; //@ref Frequency
	enum DoubleSpeed		Double_Speed;	
	
	}SPI_Config;

//////////////////////////////MACROS//////////////////////////////
// SPCR Bits
#define SPR0	0
#define SPR1	1
#define CPHA	2
#define CPOL	3
#define MSTR	4
#define DORD	5
#define SPE		6
#define SPIE	7

// SPSR Bits
#define SPI2X	0
#define WCOL	6
#define SPIF	7

//@ref Frequency
#define F_DIV4		0b00
#define	F_DIV16		0b01
#define	F_DIV64		0b10
#define	F_DIV128	0b11

////
#define SS		4
#define MISO	6
#define MOSI	5
#define SCLK	7

///////////////APIS////////////////////
void MCAL_SPI_INIT(SPI_Config* SPIConfig );
void MCAL_SPI_SetGPIOPins(SPI_Config* SPIConfig);

uint8_t SPI_Send_And_receive(uint8_t Data);
 


#endif /* SPI_H_ */