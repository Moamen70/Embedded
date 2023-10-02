/*
 * task1.c
 *
 * Created: 10/2/2023 4:50:53 PM
 * Author : Moamen
 */ 

#include "MemoryAddress.h"
#include "Utils.h"
#include "util/delay.h"

unsigned int x = 0;


int main(void)
{
	DDRA = 0b11111111;
	CLEAR_BIT(DDRC,0);
	SET_BIT(PORTC,0);
    while (1) 
    {
		if(READ_BIT(PINC,0) == 0){
			SET_BIT(PORTA,x);
			_delay_ms(1000);
			x++;
		}
    }
}

