/*
 * Utils.h
 *
 * Created: 10/2/2023 6:27:34 PM
 *  Author: Moamen
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define SET_BIT(reg,bit)		reg |=  (1<<bit)
#define CLEAR_BIT(reg,bit)		reg &= ~(1<<bit)
#define TOGGLE_BIT(reg,bit)		reg ^=  (1<<bit)
#define READ_BIT(reg,bit)		(reg>>bit) & 1




#endif /* UTILS_H_ */