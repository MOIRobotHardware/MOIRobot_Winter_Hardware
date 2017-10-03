/******************** MOI�Ƽ� **************************
 * ʵ��ƽ̨���ײ㿪����
 * ��汾  ��ST3.5.0
 * ����    ��liang
 * �Ա�    ��
 *��Ȩ���У�����ؾ���
**********************************************************************************/
/*****�������******/

#include "motor.h"

/***
PA6--PWML
PA7--PWMR
***/
static void TIM3_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);   //��PA�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;				  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //AF ����         
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


void TIM3_Config(uint16_t PulseL,uint16_t PulseR)
{
     TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	 TIM_OCInitTypeDef  TIM_OCInitStructure;

	 /*  PWM �źŵ�ƽ����  */
	 TIM_TimeBaseInitStructure.TIM_Period = 47999;   //1.5kHz
	 TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	 TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	 TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	 TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

	 /*PWM Mode Config */
	 TIM_OCInitStructure.TIM_OCMode	= TIM_OCMode_PWM1;
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 TIM_OCInitStructure.TIM_Pulse = PulseL;
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCNPolarity_High;
	 TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	 TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);

	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 TIM_OCInitStructure.TIM_Pulse = PulseR;
	 TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	 TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);

	 TIM_ARRPreloadConfig(TIM3, ENABLE);

	 TIM_Cmd(TIM3, ENABLE);
}
/*
���������������ת����ͣ�˿�����
IN2L--PE14	   IN2R--PE15         P/R    �������ת���� 
IN1L--PE12     IN1R--PE13		  /BK	 �ƶ�����

*/

static void Motor_Control_Gpio_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE);   //��PA�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12;				  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // �������       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}
void Motor_Init(void)
{
   TIM3_GPIO_Init();
   TIM3_Config(0,0);
   Motor_Control_Gpio_Config();
}

