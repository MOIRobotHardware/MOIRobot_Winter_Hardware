#include "encoder.h"
#include "nvic.h"
#include "usart.h"

/***
T2CH1---PA0		T4CH1---PB6
T2CH2---PA1		T4CH2---PA7

***/


void TIM4_Config(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   TIM_ICInitTypeDef  TIM_ICInitStructure;

   //PB6--ch1   PB7--ch2 
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ��TIM4ʱ��	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOAʱ�� 
   
   GPIO_StructInit(&GPIO_InitStructure);
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//PB6 PB7��������
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure); 

   TIM_DeInit(TIM4);
   TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
   TIM_TimeBaseStructure.TIM_Period = 600*4-1;  //��ʱ����װֵ TIMx_ARR
   TIM_TimeBaseStructure.TIM_Prescaler = 0;   //����Ƶ
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

   TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
   TIM_ICStructInit(&TIM_ICInitStructure);
   TIM_ICInitStructure.TIM_ICFilter = 7;
   TIM_ICInit(TIM4,&TIM_ICInitStructure);

   TIM_ClearFlag(TIM4, TIM_FLAG_Update);	  //���TIM4���±�־λ
   TIM_ITConfig(TIM4, TIM_IT_Update,ENABLE);  //���и����ж�
   TIM4->CNT = 0;//Reset counter
   TIM_Cmd(TIM4, ENABLE); //������ʱ��4

   NVIC_Config(2);

}

void TIM2_Config(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   TIM_ICInitTypeDef  TIM_ICInitStructure;

   //PA0--ch1   PA1--ch2 
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ��TIM2ʱ��	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

   GPIO_StructInit(&GPIO_InitStructure);
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//PA0 PA1��������
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
 

   TIM_DeInit(TIM2);
   TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
   TIM_TimeBaseStructure.TIM_Period = 600*4-1;  //��ʱ����װֵ TIMx_ARR
   TIM_TimeBaseStructure.TIM_Prescaler = 0;   //����Ƶ
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

   TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
   TIM_ICStructInit(&TIM_ICInitStructure);
   TIM_ICInitStructure.TIM_ICFilter = 7;
   TIM_ICInit(TIM2,&TIM_ICInitStructure);

   TIM_ClearFlag(TIM2, TIM_FLAG_Update);	  //���TIM2���±�־λ
   TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);  //���и����ж�
   TIM2->CNT = 0;//Reset counter
   TIM_Cmd(TIM2, ENABLE); //������ʱ��2

   NVIC_Config(3);
}
/****
������TIM7���ã��������Ĳ�������
���룺��ʱ������ֵ Ԥ��Ƶֵ
�������
****/

void TIM7_Config(uint16_t arr, uint16_t psc)      //��������������
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);//ʹ��TIM4ʱ��

   NVIC_Config(0);

   TIM_DeInit(TIM7);
   TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
   TIM_TimeBaseStructure.TIM_Period = arr-1;  //��ʱ����װֵ TIMx_ARR
   TIM_TimeBaseStructure.TIM_Prescaler = psc-1;   //����Ƶ
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

   TIM_ClearFlag(TIM7,TIM_FLAG_Update);     //����жϱ�־
   TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //ʹ�ܶ�ʱ���ж�

   TIM_Cmd(TIM7, ENABLE); //������ʱ��7
}


uint16_t EcdL1=0,EcdR1=0,EcdL0=0,EcdR0=0;
int16_t EcdL,EcdR;
float SpeedL=0.0;
void TIM7_IRQHandler(void)
{
      if(TIM7->SR&0x0001) //����жϱ�־
	{  	   
	   TIM_Cmd(TIM7, DISABLE);

	   EcdL1=TIM2->CNT;
	   EcdR1=TIM4->CNT;
	   printf("\r\nEcdL1=%d",EcdL1);
	   printf("\r\nEcdR1=%d",EcdR1);

	   EcdL=EcdL1-EcdL0;
	   EcdR=EcdR1-EcdR0;

       if(EcdL<-2000)	   //������ת�����
	   {
	     SpeedL=(2400-EcdL0+EcdL1)/(0.05*4)*60;	   	   
	   }
	   else if(EcdL>2000)	   //������ת�����
	   {
	     SpeedL=(2400-EcdL1+EcdL0)/(0.05*4)*60;	   	   
	   }
	   else SpeedL=EcdL/(0.05*4)*60;     //��λ��r/min
	   printf("SpeedL:%.2f\r\n",SpeedL);
	   EcdL0=EcdL1;
	}
	
	TIM7->SR&=~(1<<0);//����жϱ�־λ	
    TIM_Cmd(TIM7,ENABLE);
}




