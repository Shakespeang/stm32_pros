#ifndef _PID_H_
#define _PID_H_
//结构体定义

#include "main.h"

typedef struct {
    float target_val;             //目标值，相当于SetValue
    float Kp;                       //比例系数Proportional
    float Ki;                       //积分系数Integral
    float Kd;                       //微分系数Derivative
    float err;                       //当前误差
    float err_last;                      //前一次误差 e(k-1)
    float I;                      //再前一次误差 e(k-2)
    int32_t OUT;                      //PID输出
    float OUT_MAX;                      //PID输出
    float I_MAX;
} PID_IncTypeDef;

extern struct PID_IncTypeDef chassis_pid_speed;
extern struct PID_IncTypeDef	chassis_pid_pos;

extern void pid_culate(volatile PID_IncTypeDef*pid1,float now,float target);



#endif
