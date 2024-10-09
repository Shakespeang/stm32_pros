#include "tx.h"
#include "calculate.h"

void TX(void * argument)
{
	uint32_t current_time;	
	for(;;)
	{
		current_time=xTaskGetTickCount();
		moto_set(1,1,1,v1*8192/30000);
		set_moto_current_all(&hcan1,2,moto_base1[0].pid_speed.OUT,moto_base1[1].pid_speed.OUT,moto_base1[2].pid_speed.OUT,0);
		vTaskDelayUntil(&current_time,TX_TIM_DELAY);
	}
}
