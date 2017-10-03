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
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能TIM4时钟	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIOA时钟 
   
   GPIO_StructInit(&GPIO_InitStructure);
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//PB6 PB7浮空输入
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure); 

   TIM_DeInit(TIM4);
   TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
   TIM_TimeBaseStructure.TIM_Period = 600*4-1;  //定时器重装值 TIMx_ARR
   TIM_TimeBaseStructure.TIM_Prescaler = 0;   //不分频
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

   TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
   TIM_ICStructInit(&TIM_ICInitStructure);
   TIM_ICInitStructure.TIM_ICFilter = 7;
   TIM_ICInit(TIM4,&TIM_ICInitStructure);

   TIM_ClearFlag(TIM4, TIM_FLAG_Update);	  //清除TIM4更新标志位
   TIM_ITConfig(TIM4, TIM_IT_Update,ENABLE);  //运行更新中断
   TIM4->CNT = 0;//Reset counter
   TIM_Cmd(TIM4, ENABLE); //启动定时器4

   NVIC_Config(2);

}

void TIM2_Config(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   TIM_ICInitTypeDef  TIM_ICInitStructure;

   //PA0--ch1   PA1--ch2 
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能TIM2时钟	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟

   GPIO_StructInit(&GPIO_InitStructure);
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//PA0 PA1浮空输入
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
 

   TIM_DeInit(TIM2);
   TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
   TIM_TimeBaseStructure.TIM_Period = 600*4-1;  //定时器重装值 TIMx_ARR
   TIM_TimeBaseStructure.TIM_Prescaler = 0;   //不分频
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

   TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
   TIM_ICStructInit(&TIM_ICInitStructure);
   TIM_ICInitStructure.TIM_ICFilter = 7;
   TIM_ICInit(TIM2,&TIM_ICInitStructure);

   TIM_ClearFlag(TIM2, TIM_FLAG_Update);	  //清除TIM2更新标志位
   TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);  //运行更新中断
   TIM2->CNT = 0;//Reset counter
   TIM_Cmd(TIM2, ENABLE); //启动定时器2

   NVIC_Config(3);
}
/****
函数：TIM7配置，编码器的采样周期
输入：定时器重载值 预分频值
输出：无
****/

void TIM7_Config(uint16_t arr, uint16_t psc)      //编码器采样周期
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);//使能TIM4时钟

   NVIC_Config(0);

   TIM_DeInit(TIM7);
   TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
   TIM_TimeBaseStructure.TIM_Period = arr-1;  //定时器重装值 TIMx_ARR
   TIM_TimeBaseStructure.TIM_Prescaler = psc-1;   //不分频
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

   TIM_ClearFlag(TIM7,TIM_FLAG_Update);     //清除中断标志
   TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //使能定时器中断

   TIM_Cmd(TIM7, ENABLE); //启动定时器7
}


uint16_t EcdL1=0,EcdR1=0,EcdL0=0,EcdR0=0;
int16_t EcdL,EcdR;
float SpeedL=0.0;
void TIM7_IRQHandler(void)
{
      if(TIM7->SR&0x0001) //溢出中断标志
	{  	   
	   TIM_Cmd(TIM7, DISABLE);

	   EcdL1=TIM2->CNT;
	   EcdR1=TIM4->CNT;
	   printf("\r\nEcdL1=%d",EcdL1);
	   printf("\r\nEcdR1=%d",EcdR1);

	   EcdL=EcdL1-EcdL0;
	   EcdR=EcdR1-EcdR0;

       if(EcdL<-2000)	   //持续正转有溢出
	   {
	     SpeedL=(2400-EcdL0+EcdL1)/(0.05*4)*60;	   	   
	   }
	   else if(EcdL>2000)	   //持续反转有溢出
	   {
	     SpeedL=(2400-EcdL1+EcdL0)/(0.05*4)*60;	   	   
	   }
	   else SpeedL=EcdL/(0.05*4)*60;     //单位：r/min
	   printf("SpeedL:%.2f\r\n",SpeedL);
	   EcdL0=EcdL1;
	}
	
	TIM7->SR&=~(1<<0);//清除中断标志位	
    TIM_Cmd(TIM7,ENABLE);
}




