#ifndef _CALCULATE_H
#define _CALCULATE_H

#include "freertos.h"
#include "main.h"
#include "cmsis_os.h"
#include "can_rec.h"
     


extern float v1,v2,v3,v4;  	
extern void pid_init(volatile PID_IncTypeDef*pid1,float kp,float ki,float kd,float out_max,float i_max);
extern void moto_set(int can_choose,int ID_choose,int control_mood,float set);
#endif
