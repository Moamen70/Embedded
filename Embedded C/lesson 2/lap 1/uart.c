
#include "uart.h"

typedef volatile unsigned int   vuint32_t ;
typedef unsigned int            uint32 ;

#define UART0DR  *((vuint32_t * const)((uint32*) 0x101f1000))

void Uart_Send_String (unsigned char* P_tx_atring ){
	while(*P_tx_atring != '\0')
	{
		UART0DR = (uint32)*P_tx_atring;
		P_tx_atring++;
	}
}