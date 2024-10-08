#include "calculate.h"
#include "math.h"
//int temp_target=500;
void CALCULATE(void * argument)
{
osDelay(1000);
	double pos[3]={0,0,0},des[3]={5000,0,180};
	pid_init(&moto_base1[0].pid_pos,0.05,0,0,5000,5000);
	pid_init(&moto_base1[0].pid_speed,10,1,0,5000,5000);
	pid_init(&moto_base1[1].pid_pos,0.05,0,0,5000,5000);
	pid_init(&moto_base1[1].pid_speed,10,1,0,5000,5000);
	pid_init(&moto_base1[2].pid_pos,0.05,0,0,5000,5000);
	pid_init(&moto_base1[2].pid_speed,10,1,0,5000,5000);
	while(1)
	{
	osDelay(1);
	}
}

/*
can_choose:1为CAN1
						2为CAN2
ID_choose :选择1-8
control_mode:1为角度控制
							2：速度控制


*/

void moto_set(int can_choose,int ID_choose,int control_mode,int set)
{
 struct moto_measure_t moto_temp;
	if(can_choose==1)moto_temp=moto_base1[ID_choose-1];
	else if(can_choose==2)moto_temp=moto_base2[ID_choose-1];
	
	if(control_mode==1)
	{
	pid_culate(&moto_temp.pid_pos,moto_temp.total_angle,set);
	pid_culate(&moto_temp.pid_speed,moto_temp.speed_rpm,moto_temp.pid_pos.OUT);
	}
	if(control_mode==2)
	{
		pid_culate(&moto_temp.pid_speed,moto_temp.speed_rpm,set);
	}
	if(can_choose==1)moto_base1[ID_choose-1]=moto_temp;
	else if(can_choose==2)moto_base2[ID_choose-1]=moto_temp;

}
 void pid_init(volatile PID_IncTypeDef*pid1,float kp,float ki,float kd,float out_max,float i_max)
 {
 
   pid1->Kp=kp;
	 pid1->Kd=kd;
	 pid1->Ki=ki;
	 pid1->OUT_MAX=out_max;
	 pid1->I_MAX=i_max;
 }
