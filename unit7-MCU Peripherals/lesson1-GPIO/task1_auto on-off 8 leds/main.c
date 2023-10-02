/*
 * task1.c
 *
 * Created: 10/2/2023 4:50:53 PM
 * Author : Moamen
 */ 

#include "MemoryAddress.h"
#include "Utils.h"
#include "util/delay.h"



int main(void)
{
	DDRA = 0xff;
    while (1) 
    {
		for(int i = 0; i < 8 ; i++){
			SET_BIT(PORTA,i);
			_delay_ms(1000);
		}
		
		for(int i = 0; i < 8 ; i++){
			CLEAR_BIT(PORTA,i);
			_delay_ms(1000);
		}	
    }
}

