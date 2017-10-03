/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ��ͨ�����Եĳ����ն���Ƭ���������ݣ���Ƭ�������յ������ݷ��ص��ԣ�
 *         ������ʾ�ڳ����ն��ϡ��õ��Ǵ���1���жϷ�ʽ��         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
*********************************************************************************/
#include "stm32f10x.h"
#include "usart.h"
#include "string.h"
#include "led.h"
#include "motor.h"
#include "encoder.h"


/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */

extern uint8_t Re_buf[11],sign;
int main(void)
{	
	float angle;
    
	/****USART*****/
	USART1_Config();			/* USART1 config 115200 8-N-1 */
//  USART2_Config();
//	NVIC_Configuration();

	/****LED******/
	LED_GPIO_Config();
	LED0_ON;

	/****Motor****/
	Motor_Init();

	/****TIMER****/
	TIM4_Config();
    TIM2_Config();
	TIM7_Config(50000, 72);    //50ms����


    while(1)
	{
       TIM3_Config(1000,1000);
//		if(sign)
//		{
//		  angle =read_angle(&sign,Re_buf);
//		  //printf("\r\nZ�᣺%.2f",angle);
//		}	
	}
}
/******************* (C) COPYRIGHT 2017 MIO Team *****END OF FILE************/
