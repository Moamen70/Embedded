/*
 * MAX7221_lab.c
 *
 * Created: 11/7/2023 2:29:27 PM
 * Author : Moamen
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "Commands.h"

#define SS		4
#define MOSI	5
#define SCLK	7

void SPI_INIT(void)
{
	DDRB |= (1<<SS | 1<<MOSI | 1<<SCLK);
	
	SPCR |= (1<<SPE | 1<<MSTR | 1<<SPR0);
}

void sendCommand(unsigned char cmd)
{
	SPDR = cmd;
	while(!(SPSR & 1<<7));
}

void sendData(unsigned char x)
{
	SPDR = x;
	while(!(SPSR & 1<<7));
}

void transmitDataToMax7221(unsigned char cmd,unsigned char x)
{
	PORTB &= ~(1<< SS);
	
	sendCommand(cmd);
	sendData(x);
	
	PORTB |= (1<< SS);
}


int main(void)
{
	unsigned char counter = 0;
	SPI_INIT();
	
	transmitDataToMax7221(Decoding_Mode,0xFF);
	transmitDataToMax7221(Scan_Limit,0x07);
	transmitDataToMax7221(Intensity,0x0F);
	transmitDataToMax7221(Turn_On_Off ,0x01);
	
    while (1) 
    {
		for(unsigned char index = SEG0 ; index <= SEG7 ; index++)
		{
			transmitDataToMax7221(index, counter++);
			_delay_ms(1000);
		}
    }
}

