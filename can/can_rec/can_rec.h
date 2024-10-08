#ifndef __CAN_rec_H
#define __CAN_rec_H
#include "main.h"
#include "can.h"
#include "usart.h"

extern void my_can_filter_init_recv_all(CAN_HandleTypeDef* _hcan);
extern uint8_t can_transmit(CAN_HandleTypeDef* hcan);

#endif
