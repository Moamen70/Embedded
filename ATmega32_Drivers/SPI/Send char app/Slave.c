/*
 * SlaveSPI.c
 *
 * Created: 11/7/2023 12:23:25 PM
 * Author : Moamen
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define MISO	6

void SlaveINIT(void)
{
	DDRB |= (1<<MISO);
	
	SPCR |= (1<<SPE | 1<<SPR0);
	SPSR &= ~(1<<MSTR);
}

unsigned char SlaveRecive()
{
	unsigned char x = SPDR;
	while(!(SPSR & 1<<7));
	return x;
}


int main(void)
{
	SlaveINIT();
	DDRA = 0xFF;
    /* Replace with your application code */
	unsigned char x ;
   while(1)
   {
		x = SlaveRecive();
		_delay_ms(1000);
		PORTA = x;   
   }
}

