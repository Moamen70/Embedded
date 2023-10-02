/*
 * MemoryAddress.h
 *
 * Created: 10/2/2023 6:25:12 PM
 *  Author: Moamen
 */ 


#ifndef MEMORYADDRESS_H_
#define MEMORYADDRESS_H_

#define PORTA		*(volatile unsigned char *)(0x3B)
#define DDRA		*(volatile unsigned char *)(0x3A)
#define PINA		*(volatile unsigned char *)(0x39)

#define PORTC		*(volatile unsigned char *)(0x35)
#define DDRC		*(volatile unsigned char *)(0x34)
#define PINC		*(volatile unsigned char *)(0x33)


#endif /* MEMORYADDRESS_H_ */