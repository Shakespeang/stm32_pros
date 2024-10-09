#include "pid.h"

void pid_culate(volatile PID_IncTypeDef*pid1,float now,float target)
{
pid1->err=target-now;
pid1->I+=pid1->err;

if(pid1->I>pid1->I_MAX)pid1->I=pid1->I_MAX;
	else if(pid1->I<-pid1->I_MAX)pid1->I=-pid1->I_MAX;

	
	
pid1->OUT=pid1->Kp*pid1->err+
					pid1->Ki*pid1->I+
					pid1->Kd*(pid1->err-pid1->err_last);
	pid1->err_last=pid1->err;
	
	if(pid1->OUT>pid1->OUT_MAX)pid1->OUT=pid1->OUT_MAX;
	else if (pid1->OUT<-pid1->OUT_MAX)pid1->OUT=-pid1->OUT_MAX;
	
}


