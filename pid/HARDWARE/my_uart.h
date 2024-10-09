#ifndef _MY_UART_
#define _MY_UART_

#include "stdio.h"	
#include "stm32f4xx_hal.h"
#include "main.h"

extern float pos_x;
extern float pos_y;
extern float zangle;
void Data_Analyse(uint8_t rec);
void Stract(char strDestination[],char strSource[],int num);
#endif
