/*
 * ATmegaDrivers.c
 *
 * Created: 10/22/2023 12:04:17 PM
 * Author : Moamen
 */ 

#define F_CPU 1000000UL

#include "ATmega32_Device_Header.h"
#include "GPIO.h"
#include "lcd.h"


GPIO_init()
{
	GPIO_PinConfig_t PinConfig;
	
	/* AMIT LCD Data Lines
	 * Configure the PORTA Pins (4..7) as Output
	 * LCD_D4 -> PORTA.4
	 * LCD_D5 -> PORTA.5
	 * LCD_D6 -> PORTA.6
	 * LCD_D7 -> PORTA.7
	 */
	
	// Configure PIN4 as Output(push-pull)
	PinConfig.GPIO_PinNumber = GPIO_PIN_4;
	PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOA, &PinConfig);
	
	// Configure PIN5 as Output(push-pull)
	PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOA, &PinConfig);
	
	// Configure PIN6 as Output(push-pull)
	PinConfig.GPIO_PinNumber = GPIO_PIN_6;
	PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOA, &PinConfig);
	
	// Configure PIN7 as Output(push-pull)
	PinConfig.GPIO_PinNumber = GPIO_PIN_7;
	PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOA, &PinConfig);
	
	
	/* AMIT LCD Control Lines
	 * Configure the PortB PINs as Output(push-pull)
	 * LCD_RS -> PORTB.1
	 * LCD_RW -> PORTB.2
	 * LCD_E  -> PORTB.3
	 */
	
	// Configure PIN1 as Output(push-pull)
	PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOA, &PinConfig);
	
	// Configure PIN2 as Output(push-pull)
	PinConfig.GPIO_PinNumber = GPIO_PIN_2;
	PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOA, &PinConfig);
	
	// Configure PIN3 as Output(push-pull)
	PinConfig.GPIO_PinNumber = GPIO_PIN_3;
	PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	MCAL_GPIO_Init(GPIOB, &PinConfig);
	
	//#########################################
}


int main(void)
{
	// Initialize the GPIO
	GPIO_init();
	// Initialize the LCD
	LCD_INIT();
	
	LCD_WRITE_STRING("Learn In Depth");
	
    while (1) 
    {
		
    }
	return 0;
}

