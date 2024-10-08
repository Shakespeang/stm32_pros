#ifndef __CAN_rec_H
#define __CAN_rec_H
#include "main.h"
#include "can.h"
#include "string.h"
#include "pid.h"
#define FILTER_BUF_LEN 5

#define chassis_ID_1 0
#define chassis_ID_2 1
#define chassis_ID_3 2


struct moto_measure_t {
    int16_t  	command; //pid控制器切换
    int16_t     pid_cnt;
    int16_t	 	speed_rpm;
    int16_t  	real_current;
    int16_t  	given_current;
    uint8_t  	temp;
    int32_t 	angle;				//abs angle range:[0,8191]
    int32_t 	last_angle;			//abs angle range:[0,8191]
    int16_t		mid_angle;
    int32_t		round_cnt;
    long long		total_angle;
    long long     last_total_angle;
    int32_t		dif_angle;
    int32_t		dif_angle_set;
    long long		total_angle_set;
    int32_t     gimbal_angle;
    uint8_t		buf_idx;
    uint16_t	angle_buf[FILTER_BUF_LEN];
    uint16_t	fited_angle;
    uint32_t	msg_cnt;
    uint32_t    can_send;//最终发送给电机的数据
    PID_IncTypeDef pid_current;//电流环PID
    PID_IncTypeDef pid_speed;//速度环PID
    PID_IncTypeDef pid_pos;//位置环PID
};

extern CAN_HandleTypeDef hcan1, hcan2;
void my_can_filter_init_recv_all(CAN_HandleTypeDef* _hcan);
extern uint8_t set_moto_current_all(CAN_HandleTypeDef* hcan, int16_t mark, int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
uint8_t send_9025_message(CAN_HandleTypeDef* hcan, uint8_t mark, uint8_t motorID, uint8_t Tx1, uint8_t Tx2, uint8_t Tx3, uint8_t Tx4, uint8_t Tx5, uint8_t Tx6, uint8_t Tx7);
volatile extern struct moto_measure_t moto_base1[11], moto_base2[11], yaw_moto_9025;	  //电机总数
typedef enum {
    CAN_3508Moto_ALL_ID = 0x200,
    CAN_3508Moto_ID1 = 0x201,
    CAN_3508Moto_ID2 = 0x202,
    CAN_3508Moto_ID3 = 0x203,
    CAN_3508Moto_ID4 = 0x204,
    CAN_6020Moto_ID1 = 0x205,
    CAN_6020Moto_ID2 = 0x206,
    CAN_6020Moto_ID3 = 0x207,
    CAN_6020Moto_ID4 = 0x208,
    CAN_6020Moto_ID5 = 0x209,
    CAN_6020Moto_ID6 = 0x20A,
    CAN_6020Moto_ID7 = 0x20B,
    CAN_DriverPower_ID = 0x80,

}CAN_Message_ID;             


#endif
