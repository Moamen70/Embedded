/*
 * stm32f103x8_spi_drivers.h
 *
 *  Created on: Nov 5, 2023
 *      Author: Moamen
 */

#ifndef INC_STM32F103X8_SPI_DRIVERS_H_
#define INC_STM32F103X8_SPI_DRIVERS_H_

#include "STM32F103x8.h"
#include "stm32f103x8_gpio_drivers.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------
// Config structure
struct s_IRQ_SCR{
	uint8_t TXE:1;
	uint8_t RXNT:1;
	uint8_t ERR:1;
	uint8_t reserved:5;
};

typedef struct{
	uint16_t Device_mode;               //Specifies the SPI operating mode @Ref SPI_Device_Mode

	uint16_t comunication_mode;         //Specifies the SPI bidirectional mode state @Ref SPI_communication_Mode

	uint16_t frame_format;              //Specifies LSB or MSB @Ref SPI_Frame_Format_Mode

	uint16_t data_size;                 //Specifies Data Size 8Bit or 16Bit @Ref SPI_Data_Size_Mode

	uint16_t CLK_Polarity;              //Specifies CLK_Polarity idle high or idle low @Ref SPI_CLK_Polarity_Mode

	uint16_t CLK_Phase;                 //Specifies CLK_Phase First edge First or Second edge first @Ref SPI_CLK_Phase_Mode

	uint16_t Nss;                      //Specifies NSS is signal managed by SSM bit (SW internal bit (SSI Bit)) or HardWare (NSS pin)  @Ref SPI_NSS_Mode

	uint16_t Bound_rate_pres;           /*Specifies Baud_Rate_Prescaler value which will be used to configure
                                      the Transmit and Receiver SCK Clock. Set This Parameter form @Ref SPI_Baud_Rate_Prescaler
                                      Take care you have to configure RCC to enter the correct clock to APP1 >>to SPI2 or APP2 >>to SPI1 */

	uint16_t IRQ_Enable;             //@Ref SPI_IRQ_Enable

	void(* p_IRQ)(struct s_IRQ_SCR irq_src);  //Set C Function() To call when IRQ happened
                                              //We make the function tack structure to know what means any interrupt
}SPI_Config_t;


////////////////////////@ref///////////////////////////////////
//@Ref SPI_Device_Mode
#define SPI_Device_Slave		0
#define SPI_Device_Master		(1<<2)

//@Ref SPI_communication_Mode
#define SPI_commun_1_line_Bidir_RE_Only		(1<<15) // CR1 Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_commun_1_line_Bidir_TE_Only		(1<<15 | 1<<14) // CR1. Bit 15 BIDIMODE: Bidirectional data mode enable / Bit 14 BIDIOE: Output enable in bidirectional mode
#define SPI_commun_2_lines					0
#define SPI_commun_2_lines_RE_Only			(1<<10) // CR1. Bit 10 RXONLY: Receive only

//@Ref SPI_Frame_Format_Mode
#define SPI_Frame_Format_LSB		(1<<7)	//CR1.Bit 7 LSBFIRST: Frame format
#define SPI_Frame_Format_MSB		0

//@Ref SPI_Data_Size_Mode
#define SPI_Data_Size_8bits			0
#define SPI_Data_Size_16bits		(1<<11) // CR1.Bit 11 DFF: Data frame format

//@Ref SPI_CLK_Polarity_Mode
#define SPI_CLK_Polarity_0_IDLE		0
#define SPI_CLK_Polarity_1_IDLE		(1<<1) //CR1.Bit1 CPOL: Clock polarity

//@Ref SPI_CLK_Phase_Mode
#define SPI_CLK_Phase_1_Edge__First		0
#define SPI_CLK_Phase_2_Edge__First		(1<<0) //CR1.Bit 0 CPHA: Clock phase

//@Ref SPI_NSS_Mode
//HW
#define SPI_NSS_Hard_slave						0
#define SPI_NSS_Hard_Master_Output_EN			(1<<2) //CR2.Bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_Master_Output_DIS			~(1<<2)

//SW
#define SPI_NSS_Soft_Internal_RESET 			(1<<9)
#define SPI_NSS_Soft_Internal_SET                (1<<9)|(1<<8) // Bit 9 SSM: Software slave management / Bit 8 SSI: Internal slave select

//@Ref SPI_Baud_Rate_Prescaler
#define SPI_Baud_Rate_Div_2				(0b000 << 3) //	fPCLK/2
#define SPI_Baud_Rate_Div_4				(0b001 << 3) //	fPCLK/4
#define SPI_Baud_Rate_Div_8				(0b010 << 3) //	fPCLK/8
#define SPI_Baud_Rate_Div_16			(0b011 << 3) //	fPCLK/16
#define SPI_Baud_Rate_Div_32			(0b100 << 3) //	fPCLK/32
#define SPI_Baud_Rate_Div_64			(0b101 << 3) //	fPCLK/64
#define SPI_Baud_Rate_Div_128			(0b110 << 3) //	fPCLK/128
#define SPI_Baud_Rate_Div_256			(0b111 << 3) //	fPCLK/256

//@Ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE				0
#define SPI_IRQ_Enable_TXEIE_EN			(1<<7) // Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE_EN		(1<<6) // Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE_EN			(1<<5) // Bit 5 ERRIE: Error interrupt enable

/*
 * ========================================================================================
 *                         APIs Supported by "MCAL USART DRIVER"
 * ========================================================================================
 *
 */

enum PollingMechism
{
	Enable,
	Disable
};

void MCAL_SPI_INIT(SPI_TypeDef* SPIx,SPI_Config_t* SPI_Config);
void MCAL_SPI_DeINIT(SPI_TypeDef* SPIx);
void MCAL_SPI_GPIO_SET_PINS(SPI_TypeDef* SPIx);
void MCAL_SPI_SEND_DATA(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn);
void MCAL_SPI_RECEIVE_DATA(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn);
void MCAL_SPI_TX_RX(SPI_TypeDef* SPIx,uint16_t* pTxBuffer,enum PollingMechism PollingEn);

#endif /* INC_STM32F103X8_SPI_DRIVERS_H_ */
