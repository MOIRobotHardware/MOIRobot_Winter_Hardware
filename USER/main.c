/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：通过电脑的超级终端向单片机发送数据，单片机将接收到的数据发回电脑，
 *         ：并显示在超级终端上。用的是串口1的中断方式。         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
*********************************************************************************/
#include "stm32f10x.h"
#include "usart.h"
#include "string.h"
#include "led.h"
#include "motor.h"
#include "encoder.h"


/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
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
	TIM7_Config(50000, 72);    //50ms采样


    while(1)
	{
       TIM3_Config(1000,1000);
//		if(sign)
//		{
//		  angle =read_angle(&sign,Re_buf);
//		  //printf("\r\nZ轴：%.2f",angle);
//		}	
	}
}
/******************* (C) COPYRIGHT 2017 MIO Team *****END OF FILE************/
