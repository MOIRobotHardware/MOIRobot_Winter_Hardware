#include "nvic.h"
#include "misc.h"


void TIM4_NVIC_Config(NVIC_InitTypeDef NVIC_InitStructure2)
{
	NVIC_InitStructure2.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority =1;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure2);

}
void TIM2_NVIC_Config(NVIC_InitTypeDef NVIC_InitStructure3)
{
	NVIC_InitStructure3.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure3.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure3.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure3.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure3);

}
void TIM7_NVIC_Config(NVIC_InitTypeDef NVIC_InitStructure0)
{
    NVIC_InitStructure0.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure0.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure0.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure0.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure0);

}
void NVIC_Config(uint8_t IT_flag)
{
   NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

   if(IT_flag==0)
   {
   	 TIM7_NVIC_Config(NVIC_InitStructure);   
   }
   if(IT_flag==2)
   {
   	 TIM4_NVIC_Config(NVIC_InitStructure);  
   }
   if(IT_flag==3)
   {
   	 TIM2_NVIC_Config(NVIC_InitStructure);  
   }
} 

