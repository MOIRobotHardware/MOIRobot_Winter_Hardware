#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
void LED_GPIO_Config(void);

#define LED0_OFF  GPIO_SetBits (GPIOD,GPIO_Pin_9)
#define LED0_ON   GPIO_ResetBits (GPIOD,GPIO_Pin_9)

#define LED1_OFF  GPIO_SetBits (GPIOD,GPIO_Pin_11)
#define LED1_ON   GPIO_ResetBits (GPIOD,GPIO_Pin_11)


#endif
