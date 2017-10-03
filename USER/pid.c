

#include "pid.h"

float pidL1=0.0,pidL2=0.0,pidR1=0.0,pidR2=0.0;

PID pidL={0,0,0.0,0.0,0.0,0.0};
PID pidR={0,0,0.0,0.0,0.0,0.0};

int pid_caculate(PID *pidx,int8_t Setn,float Actualn)
{
    
    int16_t Pulse;
	pidx->err=Setn-Actualn;

	pidx->pwm=pidx->pwm0+pidx->kp*pidx->err-pidx->ki*pidx->err_last;
    if(pidx->pwm<0)
	{
	  pidx->pwm=0;	
	}
	else if(pidx->pwm>18)
	{
	  pidx->pwm=18;	
	}
	else pidx->pwm=pidx->pwm;

	Pulse=pidx->pwm*145;
	pidx->pwm0=pidx->pwm;
	pidx->err_last=pidx->err;
	return Pulse;
}

