/*
 * Timers.c
 *
 * Created: 12/17/2023 11:23:59 AM
 *  Author: Moamen
 */ 

#include "Timers.h"

/******************************************************************************
*                               GLOBAL & EXTERN VARIABLES                     *
*******************************************************************************/
void (* CALLBACK_OVF)(void) ;
void (* CALLBACK_CM)(void) ;
uint8_t u8_TOVNumber;
STIMER0_CONFIG* TIMER0_Configurations;

/******************************************************************************
*								 APIS IMPLEMENTATION			              *
*******************************************************************************/
E_STATUS_t TIMER0_Init(STIMER0_CONFIG* configuartion)
{
	E_STATUS_t u8_Retval = E_NOK;
	if (NULL_PTR == configuartion)
	{
		u8_Retval = E_NOK;
	}
	else
	{
		TIMER0_Configurations = configuartion;
		if ((NORMAL == TIMER0_Configurations->mode) || (CTC == TIMER0_Configurations->mode))
		{
			TCCR0 |= TIMER0_Configurations->mode;
			u8_Retval = E_OK;
		}
		else
		{
			u8_Retval = E_NOK;
		}
		if ((NO_CLK_SRC <= TIMER0_Configurations->clk) && (EXT_CLK_RISING >= TIMER0_Configurations->clk))
		{
			TCCR0 |= TIMER0_Configurations->clk;
			u8_Retval = E_OK;
		}
		else
		{
			u8_Retval = E_NOK;
		}
		if ((OCIE_DISABLE == TIMER0_Configurations->ocmInterrupt) || (OCIE_ENABLE == TIMER0_Configurations->ocmInterrupt))
		{
			TIMSK |= TIMER0_Configurations->ocmInterrupt;
			u8_Retval = E_OK;
		}
		else
		{
			u8_Retval = E_NOK;
		}
		if ((TOIE_DISABLE == TIMER0_Configurations->ovfInterrupt) || (TOIE_ENABLE == TIMER0_Configurations->ovfInterrupt))
		{
			TIMSK |= TIMER0_Configurations->ovfInterrupt;
			u8_Retval = E_OK;
		}
		else
		{
			u8_Retval = E_NOK;
		}
	}
	if (TimerMode ==TIMER0_Configurations->alarm )
	{
		DDRA = 0xFF; //Configure PORTA as output
		DDRB = 0xFF; //Configure PORTB as output
		DDRC &= ~(1<<0); //Configure PinC0 as input
		PORTB = TIMER0_Configurations->Minutes;
		u8_Retval = E_OK;
	}
	else
	{
		u8_Retval = E_NOK;
	}
	
	if (StopWatchMode ==TIMER0_Configurations->alarm )
	{
		DDRA = 0xFF; //Configure PORTA as output
		DDRB = 0xFF; //Configure PORTB as output
		DDRC &= ~(1<<0); //Configure PinC0 as input	
		PORTA = 0x00;
		PORTB = 0x00;
		u8_Retval = E_OK;
	}
	else
	{
		u8_Retval = E_NOK;
	}
	
	
	return u8_Retval;
}

E_STATUS_t TIMER0_Stop(void)
{
	E_STATUS_t u8_Retval = E_NOK;
	//TIMSK |= NO_CLK_SRC;
	TCCR0 &= ~(0x07);
	return u8_Retval;
}

E_STATUS_t TIMER0_Resume(void)
{
	E_STATUS_t u8_Retval = E_NOK;
	//TIMSK |= NO_CLK_SRC;
	TCCR0 |= TIMER0_Configurations->clk;
	return u8_Retval;
}

E_STATUS_t TIMER0_Reset(void)
{
	E_STATUS_t u8_Retval = E_NOK;
	TCCR0 = 0x00;
	TCNT0 = 0x00;
	OCR0 = 0x00;
	TIMSK = 0x00;
	TIFR = 0x00;
	return u8_Retval;
}

E_STATUS_t TIMER0_GetCompareValue(ptr_uint8_t pu8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_NOK;
	*pu8_TicksNumber = OCR0;
	return u8_Retval;
}
E_STATUS_t TIMER0_SetCompareValue(uint8_t u8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_NOK;
	OCR0 = u8_TicksNumber;
	return u8_Retval;
}

E_STATUS_t TIMER0_GetCounterValue(ptr_uint8_t pu8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_NOK;
	*pu8_TicksNumber = TCNT0;
	return u8_Retval;
}
E_STATUS_t TIMER0_SetCounterValue(uint8_t u8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_NOK;
	TCNT0 = u8_TicksNumber;
	return u8_Retval;
}

E_STATUS_t TIMER0_GetOverflowValue(ptr_uint8_t pu8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_NOK;
	*pu8_TicksNumber = u8_TOVNumber;
	return u8_Retval;
}
E_STATUS_t TIMER0_SetOverflowValue(uint8_t u8_TicksNumber)
{
	E_STATUS_t u8_Retval = E_OK;
	u8_TOVNumber = u8_TicksNumber;
	return u8_Retval;
}

void TIMER0_CALLBACK_CompareMatch_INTERRUPT(PTR_VoidFuncVoid_t callback)
{
	CALLBACK_CM = callback;
}

void TIMER0_CALLBACK_Overflow_INTERRUPT(PTR_VoidFuncVoid_t callback)
{
	CALLBACK_OVF = callback;
}

// function to calculate the seconds in timer mode
void  SecondsFunctionCounter_Timer(void){
	switch (PORTA) {
		case 0x60:
		PORTA= 0b01011001;
		break;
		
		case 0x50:
		PORTA= 0b01001001;
		break;

		case 0x40:
		PORTA= 0b00111001;
		break;

		case 0x30:
		PORTA= 0b00101001;
		break;
		
		case 0x20:
		PORTA= 0b00011001;
		break;
		
		case 0x10:
		PORTA= 0b00001001;
		break;

		default:
		PORTA-=1;
	}
}

void  SecondsFunctionCounter_StopWatch(void){
	switch (PORTA) {
		//case 0x59:
		//PORTA= 0b00000000;
		//break;
		
		case 0x49:
		PORTA= 0b01010000;
		break;

		case 0x39:
		PORTA= 0b01000000;
		break;

		case 0x29:
		PORTA= 0b00110000;
		break;
		
		case 0x19:
		PORTA= 0b00100000;
		break;
		
		case 0x9:
		PORTA= 0b00010000;
		break;

		default:
		PORTA+=1;
	}
}

ISR(TIMER0_COMP_vect)
{
	CALLBACK_CM();
}

ISR(TIMER0_OVF_vect)
{
	u8_TOVNumber++;
	CALLBACK_OVF();
}