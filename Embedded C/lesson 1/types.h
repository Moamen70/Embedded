#include <stdint.h>

#ifndef TYPES_H_
#define TYPES_H_

typedef signed char sint8_t;
typedef unsigned char usint8_t;
typedef signed short sint16_t;
typedef unsigned short usint16_t;
typedef signed int sint32_t;
typedef unsigned int usint32_t;
typedef signed long long sint64_t;
typedef unsigned long long usint64_t;

///////////////////volatile////////////////////

typedef volatile signed char vsint8_t;
typedef volatile unsigned char vusint8_t;
typedef volatile signed short vsint16_t;
typedef volatile unsigned short vusint16_t;
typedef volatile signed int vsint32_t;
typedef volatile unsigned int vusint32_t;
typedef volatile signed long long vsint64_t;
typedef volatile unsigned long long vusint64_t;

#endif
