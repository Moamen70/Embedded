/*
 * Ultrasonic.c
 *
 * Created: 1/9/2024 1:17:15 PM
 *  Author: Moamen
 */ 
#define F_CPU 8000000UL
#include "Ultrasonic.h"
#include "F:\Embedded Diploma\amega drivers\Applications\Applications\MCAL\ICU\ICU.h"
#include <avr/interrupt.h>
#include <util/delay.h>

 static uint8_t edges=0;
 uint32_t highTime;
 
 void Ultrasonic_init(void)
 {
 	Icu_ConfigType Config = {F_CPU_8,RISING};
 
 	Icu_init(&Config);
 	
 	Icu_setCallBack(Ultrasonic_edgeProcessing);
 	
 	DDRB |= (1<<5);
 }
 
 
 void Ultrasonic_Trigger(void)
 {
 	PORTB |= (1<<5);
 	_delay_ms(50);
 	PORTB &= ~(1<<5);
 }
 
 
 uint16_t Ultrasonic_readDistance(void)
 {
 	uint16_t distance = 0;
 	Ultrasonic_Trigger();
 	sei();
 	distance = (uint16_t)(((highTime * 32900UL) / 2000000UL)); 
 	//distance=(uint16_t)(((float)highTime/78));
 	cli();
 	return distance;	
 }
 
 void Ultrasonic_edgeProcessing(void)
 {
 	
 	if (edges == 0)
 	{
 		Icu_clearTimerValue();
 		Icu_setEdgeDetectionType(FALLING);
 		edges = 1;
 	}
 	else if(edges == 1)
 	{
 		highTime = Icu_getInputCaptureValue();
 		Icu_setEdgeDetectionType(RISING);
 		edges = 0;
 	}
 }

