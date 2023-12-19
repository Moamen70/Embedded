/*
 * Timer.c
 *
 * Created: 12/17/2023 1:54:10 PM
 * Author : Moamen
 */ 

#define F_CPU 8000000UL
#include "MCAL/Timers.h"

extern uint8_t u8_TOVNumber;
static uint16_t counter = 0;
STIMER0_CONFIG * G_config;

void TOIE_Callback()
{
	if(counter == 3906)
	{
		if (PORTB !=0 && PORTB == G_config->Minutes)
		{
			PORTB-=1;
			PORTA = 0b01100000;
		}
		if (PORTA != 0)
		{
			 SecondsFunctionCounter();
		}else if(PORTA == 0 && PORTB != 0)
		{
			PORTB-=1;
			PORTA = 0x59;
		}else if (PORTA == 0 && PORTB == 0 )
		{
			TIMER0_Stop();
		}
		
		counter = 0;
		}else{
		counter++;
	}
	TIFR |= 1<<0; // clear interrupt flag
}

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	sei(); //Function to enable global interrupt () - SREG I-bit = 1
	TIMER0_CALLBACK_Overflow_INTERRUPT(TOIE_Callback);
	STIMER0_CONFIG config = {NORMAL, OCIE_DISABLE, TOIE_ENABLE, PRESCALING_CLK8,3};
		
    TIMER0_Init(&config);
	
	
    while (1) 
    {
    }
}

