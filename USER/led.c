/******************** MOI�Ƽ� **************************
 * ʵ��ƽ̨���ײ㿪����
 * ��汾  ��ST3.5.0
 * ����    ��liang
 * �Ա�    ��
 *��Ȩ���У�����ؾ���
**********************************************************************************/
/*****LED******/
/**
PD9 PD11 PD13 PD15
**/
#include "led.h"

void LED_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);	 //����ʱ��

  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15 ;            
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;   
  GPIO_Init(GPIOD,&GPIO_InitStructure);
 
  GPIO_SetBits (GPIOD,GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15);
}

