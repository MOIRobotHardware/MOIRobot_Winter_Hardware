/******************** MOI科技 **************************
 * 实验平台：底层开发板
 * 库版本  ：ST3.5.0
 * 作者    ：liang
 * 淘宝    ：
 *版权所有，盗版必究。
**********************************************************************************/
/*****LED******/
/**
PD9 PD11 PD13 PD15
**/
#include "led.h"

void LED_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);	 //开启时钟

  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15 ;            
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;   
  GPIO_Init(GPIOD,&GPIO_InitStructure);
 
  GPIO_SetBits (GPIOD,GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15);
}

