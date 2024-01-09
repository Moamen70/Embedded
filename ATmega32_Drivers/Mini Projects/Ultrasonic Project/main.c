/*
 * Applications.c
 *
 * Created: 1/9/2024 5:27:34 PM
 * Author : Moamen
 */ 

#define F_CPU 8000000UL

#include "MCAl/GPIO/GPIO.h"
#include "HAl/LCD/LCD.h"
#include "MCAl/ADC/ADC.h"
#include "MCAL/ICU/ICU.h"
#include "HAL/Motor/DC_Motor.h"
#include "HAL/Sensor/LM.h"
#include "HAL/Ultrasonic/Ultrasonic.h"


uint16_t distance;
int main(void)
{
	
	LCD_INIT();
	Ultrasonic_init();
	
	while (1)
	{
		LCD_GOTOXY(0,0);
		distance = Ultrasonic_readDistance();
		LCD_WRITE_STRING("Distance = ");
		LCD_Write_Number(distance);
		LCD_WRITE_STRING("CM");
		LCD_WRITE_STRING("                    ");
	}
}


