/*
 * ADC.h
 *
 * Created: 1/1/2024 4:54:24 PM
 *  Author: Moamen
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define Ref_volt     5000
#define Res          1024

typedef enum{
	VREF_AREF,
	VREF_AVCC,
	VREF_256
}ADV_Vref_type;


//prescaler

typedef enum{
	ADC_prescaler_2 = 0,
	ADC_prescaler_4 = 2,
	ADC_prescaler_8 ,
	ADC_prescaler_16 ,
	ADC_prescaler_32 ,
	ADC_prescaler_64 ,
	ADC_prescaler_128
}ADC_Prescaler_type;


typedef enum{
	ADC_CH_0 = 0,
	ADC_CH_1 ,
	ADC_CH_2 ,
	ADC_CH_3 ,
	ADC_CH_4 ,
	ADC_CH_5 ,
	ADC_CH_6 ,
	ADC_CH_7
}ADC_Channel_type;

void ADC_init(ADV_Vref_type Vref ,ADC_Prescaler_type Prescaler);

uint16_t ADC_Read(ADC_Channel_type channel);

uint8_t GetLevel(uint16_t volt);



#endif /* ADC_H_ */