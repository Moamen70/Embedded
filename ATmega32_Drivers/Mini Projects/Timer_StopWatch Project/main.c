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
	if (TimerMode == G_config->alarm)
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
				SecondsFunctionCounter_Timer();
			}else if(PORTA == 0 && PORTB != 0)
			{
				PORTB-=1;
				PORTA = 0x59;
			}else if (PORTA == 0 && PORTB == 0 )
			{
				TIMER0_Reset();
			}
			
			counter = 0;
			}else{
			counter++;
		}
	}
	else if(StopWatchMode == G_config->alarm)
	{
		if(counter == 3906)
		{
			if (PORTA == 0x59)
			{
				PORTB += 1;
				PORTA = 0x00;
			}else
			{
				SecondsFunctionCounter_StopWatch();	
			}
	
			counter = 0;
		}else
		{
			counter++;
		}	
	}

	TIFR |= 1<<0; // clear interrupt flag
}

int main(void)
{

	sei(); //Function to enable global interrupt () - SREG I-bit = 1
	
	TIMER0_CALLBACK_Overflow_INTERRUPT(TOIE_Callback);
	
	//STIMER0_CONFIG config = {NORMAL, OCIE_DISABLE, TOIE_ENABLE, PRESCALING_CLK8,TimerMode,2};
	
	STIMER0_CONFIG config = {NORMAL, OCIE_DISABLE, TOIE_ENABLE, PRESCALING_CLK8,StopWatchMode,0};
	
	G_config = &config;
    TIMER0_Init(&config);
	
	
    while (1) 
    {
		if (!(PINC & (1<<0)))
		{
			TIMER0_Stop();
		}
		if (!(PINC & (1<<1)))
		{
			TIMER0_Resume();
		}
		if (!(PINC & (1<<2)))
		{
			TIMER0_Reset();
			PORTA = 0x00;
			PORTB = 0x00;
		}
    }
}

