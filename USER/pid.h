#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"

typedef struct 
{
   int8_t pwm0;
   int8_t pwm;
   float kp;
   float ki;
   float err_last;
   float err;
}PID;




#endif

