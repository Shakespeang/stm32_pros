#include "can_rec.h"
volatile struct moto_measure_t moto_base1[11], moto_base2[11], yaw_moto_9025;	  //电机总数
CAN_RxHeaderTypeDef	RxHeader;      //接收
void get_moto_measure(volatile struct moto_measure_t* ptr, uint8_t* Data);
/*CAN过滤器初始化*/
void my_can_filter_init_recv_all(CAN_HandleTypeDef* _hcan) {
    //can1 &can2 use same filter config
    CAN_FilterTypeDef CAN_FilterConfigStructure;

    if (_hcan == &hcan1) {
        CAN_FilterConfigStructure.FilterBank = 0;
    }
    else if (_hcan == &hcan2) {
        CAN_FilterConfigStructure.FilterBank = 14;
    }
    CAN_FilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
    CAN_FilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
    CAN_FilterConfigStructure.FilterIdHigh = 0x0000;
    CAN_FilterConfigStructure.FilterIdLow = 0x0000;
    CAN_FilterConfigStructure.FilterMaskIdHigh = 0x0000;
    CAN_FilterConfigStructure.FilterMaskIdLow = 0x0000;
    CAN_FilterConfigStructure.FilterFIFOAssignment = CAN_FilterFIFO0;
    CAN_FilterConfigStructure.SlaveStartFilterBank = 14;
    CAN_FilterConfigStructure.FilterActivation = ENABLE;

    if (HAL_CAN_ConfigFilter(_hcan, &CAN_FilterConfigStructure) != HAL_OK) {
        Error_Handler();
    }
    /* Start the CAN peripheral */
    if (HAL_CAN_Start(_hcan) != HAL_OK) {
        /* Start Error */
        Error_Handler();
    }

    /* Activate CAN RX notification */
    if (HAL_CAN_ActivateNotification(_hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
        /* Notification Error */
        Error_Handler();
    }
    /* Activate CAN TX notification */
    if (HAL_CAN_ActivateNotification(_hcan, CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK) {
        /* Notification Error */
        Error_Handler();
    }
}
/*CAN发送数据函数，返回0代表发送数据无异常，返回1代表传输异常*/
uint8_t set_moto_current_all(CAN_HandleTypeDef* hcan, int16_t mark, int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {
    CAN_TxHeaderTypeDef TxHeader;
    uint8_t TxData[8];
    if (mark == 0) {
        TxHeader.StdId = 0x1FF; //620，610：5-8;   6020：1-4
    }
    else if (mark == 1) {
        TxHeader.StdId = 0x2FF; //6020：5-8
    }
    else if (mark == 2) {
        TxHeader.StdId = 0x200; //620，610：1-4
    }
    else if (mark == 3) {
        TxHeader.StdId = 0x141; //yaw
    }
    TxHeader.DLC = 0x08;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxData[0] = (iq1 >> 8);
    TxData[1] = iq1;
    TxData[2] = (iq2 >> 8);
    TxData[3] = iq2;
    TxData[4] = iq3 >> 8;
    TxData[5] = iq3;
    TxData[6] = iq4 >> 8;
    TxData[7] = iq4;
    if (HAL_CAN_AddTxMessage(hcan, &TxHeader, TxData, (uint32_t*)CAN_TX_MAILBOX1) != HAL_OK) {
        return 1;
    }
    while (HAL_CAN_GetTxMailboxesFreeLevel(hcan) != 3);
    return 0;
}

/*CAN接收中断函数*/
uint32_t zya_cnt;
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
    uint8_t Data[8];
    HAL_StatusTypeDef HAL_RetVal;
    if (hcan == &hcan1)

		{
        HAL_RetVal = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, Data);
        if (HAL_OK == HAL_RetVal)

				{
            switch (RxHeader.StdId) 
							
						
						{
            case CAN_3508Moto_ID1: //0
            case CAN_3508Moto_ID2: //1
            case CAN_3508Moto_ID3: //2
            case CAN_3508Moto_ID4: //3
            case CAN_6020Moto_ID1: //4
            case CAN_6020Moto_ID2: //5
            case CAN_6020Moto_ID3: //6
            case CAN_6020Moto_ID4: //7
            case CAN_6020Moto_ID5: //8
            case CAN_6020Moto_ID6: //9
            case CAN_6020Moto_ID7: //10
            {
                static uint8_t i;
                i = RxHeader.StdId - CAN_3508Moto_ID1;
                moto_base1[i].msg_cnt++;
                get_moto_measure(&moto_base1[i], Data);
                //中断串口回传

            }
            break;
            
					}
						
							
						__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);  //重启中断
        }
    }
    else  if (hcan == &hcan2) {
        HAL_RetVal = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, Data);
        if (HAL_OK == HAL_RetVal) {
            switch (RxHeader.StdId) {
            case CAN_3508Moto_ID1: //0
            case CAN_3508Moto_ID2: //1
            case CAN_3508Moto_ID3: //2
            case CAN_3508Moto_ID4: //3
            case CAN_6020Moto_ID1: //4
            case CAN_6020Moto_ID2: //5
            case CAN_6020Moto_ID3: //6
            case CAN_6020Moto_ID4: //7
            case CAN_6020Moto_ID5: //8
            case CAN_6020Moto_ID6: //9
            case CAN_6020Moto_ID7: //10
            {
                static uint8_t i;
                i = RxHeader.StdId - CAN_3508Moto_ID1;
                moto_base2[i].msg_cnt++;
                get_moto_measure(&moto_base2[i], Data);

            }
						break;
            
  
            }
										__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);  //重启中断
        }

    }
}
/*电机数据包解析*/
void get_moto_measure(volatile struct moto_measure_t* ptr, uint8_t* Data) {
   
        ptr->last_angle = ptr->angle;
        ptr->last_total_angle = ptr->total_angle;
        ptr->angle = (uint16_t)(Data[0] << 8 | Data[1]);
        ptr->real_current = (int16_t)(Data[2] << 8 | Data[3]);
        ptr->speed_rpm = ptr->real_current; //这里是因为两种电调对应位不一样的信息
        ptr->given_current = (int16_t)(Data[4] << 8 | Data[5]);
        ptr->temp = Data[6];
        if (ptr->angle - ptr->last_angle > 4096)
            ptr->round_cnt--;
        else if (ptr->angle - ptr->last_angle < -4096)
            ptr->round_cnt++;
        ptr->total_angle = ptr->angle - ptr->mid_angle + ptr->round_cnt * 8192;
        //gimbal_angle代表云台相对初始位置的偏差角
        ptr->gimbal_angle = ptr->angle - ptr->mid_angle;
        if (ptr->gimbal_angle > 8192 / 2) {
            ptr->gimbal_angle -= 8192;
        }
        else if (ptr->gimbal_angle < -8192 / 2) {
            ptr->gimbal_angle += 8192;
        }
        ptr->dif_angle = ptr->total_angle - ptr->last_total_angle;
        if (ptr->msg_cnt == 1) {
            ptr->total_angle_set = ptr->total_angle;
        }
    

}



