
#include "uart.h"

unsigned char text[100] = "learn-in-depth:<Moamen>";
unsigned char const text2[100] = ".rodata section";

void main(void){
	Uart_Send_String(text);
}