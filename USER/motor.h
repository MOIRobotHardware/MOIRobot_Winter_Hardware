#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

void Motor_Init(void);
void TIM3_Config(uint16_t PulseL,uint16_t PulseR);

#define MotorL_foreward GPIO_SetBits(GPIOE,GPIO_Pin_14)
#define MotorL_backward GPIO_ResetBits(GPIOE,GPIO_Pin_14)
#define MotorL_stop     GPIO_ResetBits(GPIOE,GPIO_Pin_12)

#define MotorR_foreward GPIO_SetBits(GPIOE,GPIO_Pin_15)
#define MotorR_backward GPIO_ResetBits(GPIOE,GPIO_Pin_15)
#define MotorR_stop     GPIO_ResetBits(GPIOE,GPIO_Pin_13)

#endif
