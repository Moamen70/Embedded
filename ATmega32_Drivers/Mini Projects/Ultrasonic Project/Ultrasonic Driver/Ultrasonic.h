/*
 * Ultrasonic.h
 *
 * Created: 1/9/2024 1:16:59 PM
 *  Author: Moamen
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "avr/io.h"

void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16_t Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */