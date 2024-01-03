/*
 * Applications.c
 *
 * Created: 1/1/2024 3:27:34 PM
 * Author : Moamen
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include "GPIO/GPIO.h"
#include "LCD/LCD.h"
#include "ADC/ADC.h"


int main(void)
{
	uint16_t data ,volt, percent;
	
	uint8_t arr[16]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	//uint8_t i;
	
	LCD_INIT();
// 	
// 	MCAL_GPIO_pinDirection(PORT_A,Pin_7,Input_Statues);
// 	MCAL_GPIO_PortDirection(PORT_C,Output_Statues);
	DDRA = 0;
	ADC_init(VREF_AVCC, ADC_prescaler_128);
	
	LCD_GOTOXY(0,0);
	LCD_WRITE_STRING("perc:");
	//LCD_GOTOXY(0,7);
	LCD_WRITE_CHAR(' ');
	
	//LCD_GOTOXY(1,0);
	/* Replace with your application code */
	while (1)
	{
		
		data = ADC_Read(ADC_CH_0);
		percent = (((uint32_t)data * 100)/1024);
		//percent = (((uint16_t)volt/5000) * 100) ;
		 LCD_WRITE_STRING("Perc:");
		 LCD_WRITE_CHAR(' ');
		 LCD_GOTOXY(0,6);
		//LCD_Write_Number(data);
		LCD_Write_Number(percent);
		LCD_WRITE_CHAR('%');
		
		LCD_WRITE_STRING("                ");
		//LCD_WRITE_CHAR(' ');
		LCD_GOTOXY(1,0);
	 
		for (uint8_t i=0 ; i < (uint8_t) percent/6.25  ; i++)
		{
			if (GetLevel(percent) == 0)
			{
				
			}else LCD_WRITE_CHAR(arr[i]);
			
		}
		//LCD_WRITE_CHAR(arr[0]);
		//LCD_WRITE_COMMAND(LCD_CMD_DISP_ON_CURSOR );
 		_delay_ms(50);
 		LCD_CLEAR_SCREEN();
	}
}

