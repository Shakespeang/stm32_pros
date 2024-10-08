#include "can_rec.h"
CAN_RxHeaderTypeDef	RxHeader;

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

/*位置速度模式2的CAN发送数据函数，返回0代表发送数据无异常，返回1代表传输异常*/
uint8_t can_transmit(CAN_HandleTypeDef* hcan) {  
  CAN_TxHeaderTypeDef tx_header; 
	uint8_t can_data[8];	
	tx_header.StdId = 0x140;
	tx_header.DLC = 0x08; 
	tx_header.IDE = CAN_ID_STD;
	tx_header.RTR = CAN_RTR_DATA;
	can_data[0] = 0x01;  
	can_data[1] = 0x00;
	can_data[2] = 0x00;
	can_data[3] = 0x00;
	can_data[4] = 0x00;
	can_data[5] = 0x00;
	can_data[6] = 0x00;
	can_data[7] = 0x00;	
	if (HAL_CAN_AddTxMessage(hcan, &tx_header, can_data, (uint32_t*)CAN_TX_MAILBOX1) != HAL_OK) return 1;
	while (HAL_CAN_GetTxMailboxesFreeLevel(hcan) != 3);
	return 0;
}

void get_moto_measure(uint8_t* data);

/*CAN接收中断函数*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
	uint8_t data[8];
	HAL_StatusTypeDef HAL_RetVal;
	if (hcan == &hcan1)
	{
		HAL_RetVal = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, data);
		if (HAL_OK == HAL_RetVal)
		{
			if(RxHeader.StdId==0x140) 												
			{
					get_moto_measure(data);
			}       					
			__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);  //重启中断
		}
	}
	if (hcan == &hcan2)
	{
		HAL_RetVal = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, data);
		if (HAL_OK == HAL_RetVal)
		{
			if(RxHeader.StdId==0x140) 												
			{
					get_moto_measure(data);
			}       					
			__HAL_CAN_ENABLE_IT(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);  //重启中断
		}
	}
}
void get_moto_measure(uint8_t* data)
{
	if(data[0]==0x01)
	{
		HAL_UART_Transmit(&huart2,&data[1],1,100);
	}
}
