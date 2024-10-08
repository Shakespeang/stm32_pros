#include "tx.h"
uint16_t time_count;

void TX(void * argument)
{
osDelay(1000);
uint32_t current_time;
	


	for(;;)
{
		current_time=xTaskGetTickCount();
	
	
set_moto_current_all(&hcan1,2,moto_base1[0].pid_speed.OUT,moto_base1[1].pid_speed.OUT,moto_base1[2].pid_speed.OUT,0);
//	moto_base1[2].pid_speed.OUT
time_count++;
	vTaskDelayUntil(&current_time,TX_TIM_DELAY);
	
}
}
