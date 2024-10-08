#ifndef _PID_H_
#define _PID_H_
//�ṹ�嶨��

#include "main.h"

typedef struct {
    float target_val;             //Ŀ��ֵ���൱��SetValue
    float Kp;                       //����ϵ��Proportional
    float Ki;                       //����ϵ��Integral
    float Kd;                       //΢��ϵ��Derivative
    float err;                       //��ǰ���
    float err_last;                      //ǰһ����� e(k-1)
    float I;                      //��ǰһ����� e(k-2)
    int32_t OUT;                      //PID���
    float OUT_MAX;                      //PID���
    float I_MAX;
} PID_IncTypeDef;

extern struct PID_IncTypeDef chassis_pid_speed;
extern struct PID_IncTypeDef	chassis_pid_pos;

extern void pid_culate(volatile PID_IncTypeDef*pid1,float now,float target);



#endif
