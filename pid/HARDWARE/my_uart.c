#include "my_uart.h"
/**
 * @brief �������������������ļ����ã���Ҫ�ⲿ����
 */
float pos_x=0;
float pos_y=0;
float zangle=0;
float xangle=0;
float yangle=0;
float w_z=0;

/**
 * @brief ���ݽ�������  �����MCUƽ̨���������⣬ֻ�轫���ڽ��յ���ֵ����ú������ɽ���
 * @param  rec ���ڽ��յ����ֽ�����
 */
void Data_Analyse(uint8_t rec)
{
	static uint8_t ch;
	static union
	{
		uint8_t date[24];
		float ActVal[6];
	}posture;
	static uint8_t count=0;
	static uint8_t i=0;

	ch=rec;
	switch(count)
	{
		case 0:
			if(ch==0x0d)
				count++;
			else
				count=0;
			break;
		case 1:
			if(ch==0x0a)
			{
				i=0;
				count++;
			}
			else if(ch==0x0d);
			else
				count=0;
			break;
		case 2:
			posture.date[i]=ch;
			i++;
			if(i>=24)
			{
				i=0;
				count++;
			}
			break;
		case 3:
			if(ch==0x0a)
				count++;
			else
				count=0;
			break;
		case 4:
			if(ch==0x0d)
			{
				zangle=posture.ActVal[0];
				xangle=posture.ActVal[1];
				yangle=posture.ActVal[2];
				pos_x=posture.ActVal[3];
				pos_y=posture.ActVal[4];
				w_z=posture.ActVal[5];
			}
			count=0;
			break;
		default:
			count=0;
		break;
	}
}
void Stract(char strDestination[],char strSource[],int num){
	int i=0,j=0;
	while(strDestination[i]!='\0')i++;
	for(j=0;j<num;j++)
		strDestination[i++] = strSource[j];
}
