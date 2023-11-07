/*
 * MasterSPI.c
 *
 * Created: 11/7/2023 11:41:10 AM
 * Author : Moamen
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

///////////////////Generic Macros/////////////////
#define SS		4	
#define MOSI	5
#define MISO	6
#define SCLK	7

void MasterINIT(void)
{
	DDRB |= (1<<SS | 1<<MOSI | 1<<SCLK);
	
	SPCR |= (1<<SPE | 1<<MSTR | 1<<SPR0);
}

unsigned char MasterTransmitChar(char x)
{
	SPDR = x;
	while(!(SPSR & 1<<7)) ;
	return x;
}

int main(void)
{
	MasterINIT();
	DDRA = 0xFF;
	unsigned char data ,z;
	while(1){
		for (data = 0 ; data < 255 ; data++)
		{
		z = MasterTransmitChar(data);
		_delay_ms(1000);
		PORTA = z;
		}
	}
}

