/*
 * Applications.c
 *
 * Created: 1/1/2024 3:27:34 PM
 * Author : Moamen
 */ 

#define F_CPU 1000000UL

#include "MCAl/GPIO/GPIO.h"
#include "HAl/LCD/LCD.h"
#include "MCAl/ADC/ADC.h"
#include "HAL/Motor/DC_Motor.h"
#include "HAL/Sensor/LM.h"


int main(void)
{
	uint8_t temp ;
	char * status = "OFF";
	
	LCD_INIT();
	DcMotor_Init();
	DDRA = 0;
	ADC_init(VREF_256, ADC_prescaler_8);
	
	while (1)
	{
		temp = LM35_getTemperature();
		LCD_GOTOXY(0,2);
		LCD_WRITE_STRING("FAN IS ");
		LCD_WRITE_STRING(status);
		
		LCD_GOTOXY(1,2);
		LCD_WRITE_STRING("Temp = ");
		LCD_Write_Number(temp);
		LCD_WRITE_STRING(" C");
		if (temp < 30)
		{
			status = "OFF";
			DcMotor_Rotate(STOP,0);
		}
		else if (temp >= 30 && temp < 60)
		{
			status = "ON ";
			DcMotor_Rotate(CW,25);
		}
		else if (temp >= 60 && temp < 90)
		{
			status = "ON ";
			DcMotor_Rotate(CW,50);
		}
		else if(temp >= 90 && temp < 120)
		{
			status = "ON ";
			DcMotor_Rotate(CW,75);
		}
		else if (temp > 120)
		{
			status = "ON ";
			DcMotor_Rotate(CW,100);
		}
	}
}


