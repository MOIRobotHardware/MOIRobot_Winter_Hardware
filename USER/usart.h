#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

#define length_data 10

void USART1_Config(void);
void NVIC_Configuration(void);
void USART2_Config(void);
int fputc(int ch, FILE *f);
float read_angle(uint8_t *sign,uint8_t *Re_buf);

#endif /* __USART1_H */
