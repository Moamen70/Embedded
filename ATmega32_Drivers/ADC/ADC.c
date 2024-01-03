/*
 * ADC.c
 *
 * Created: 1/1/2024 4:54:33 PM
 *  Author: Moamen
 */ 

#include "ADC.h"

void ADC_init(ADV_Vref_type Vref ,ADC_Prescaler_type Prescaler)
{
	switch(Vref)
	{
		case VREF_AREF:
		ADMUX &= ~((1<<6) | (1<<7));
		break;
		
		case VREF_AVCC:
		ADMUX |= (1<<6);
		ADMUX &= ~(1<<7);
		break;
		
		case VREF_256:
		ADMUX |= ((1<<6) | (1<<7)) ;
		break;
	}
	
	//prescaler
	
	//keep bits
	ADCSRA &= 0xF8 ;   //1111 1000
	ADCSRA |= Prescaler ;
	
	//enable ADC
	ADCSRA |= (1<<ADEN);
}

uint16_t ADC_Read(ADC_Channel_type channel)
{
	//Keep bits
	ADMUX &= 0xE0;    //1110 0000
	ADMUX |= channel;
	
	ADCSRA |= (1<<ADSC);
	
	while(!(ADCSRA>>ADSC)&1);
	//while (ADCSRA & (1 << ADSC));
	
	//	ADCSRA |= (1<<ADIF);
	
	return ADC;
	
}

uint8_t GetLevel(uint16_t volt)
{
	return (volt/6.25);
}