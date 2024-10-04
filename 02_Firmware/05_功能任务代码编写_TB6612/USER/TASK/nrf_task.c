#include "nrf_task.h"

#include "bsp_usart.h"
#include "bluetooth_debugger.h"

RC_Ctrl_t RC_Ctrl;
uint8_t nrf_clean_flag = 0;
uint8_t nrf_clean_count = 0;
static void nrf_data_init(void);


void nrf_task(void *pvParameters)
{
	nrf_data_init();
	while(1)
	{
		usart_NRF_receive_data_unpacket();
		if(nrf_clean_flag == 1) 
		{
			nrf_clean_count = 0;
		}
		if(nrf_clean_flag == 0)
		{
			nrf_clean_count ++;
			if(nrf_clean_count > 5)
			{
				nrf_clean_count = 0;
				nrf_data_init();
			}
		}
		vTaskDelay(20);
	}
}

static void nrf_data_init()
{
	RC_Ctrl.lx_value = 2047;
	RC_Ctrl.ly_value = 2047;
	RC_Ctrl.rx_value = 2047;
	RC_Ctrl.ry_value = 2047;
	
	RC_Ctrl.gyrox = 0;
	RC_Ctrl.gyroy = 0;
	RC_Ctrl.gyroz = 0;
	
	RC_Ctrl.accx = 0;
	RC_Ctrl.accy = 0;
	RC_Ctrl.accz = 0;
	
	RC_Ctrl.KEY_YG_L = 0;
	RC_Ctrl.KEY_YG_R = 0;
	RC_Ctrl.KEY_BM_L = 0;
	RC_Ctrl.KEY_BM_R = 0;
	
	RC_Ctrl.anglex = 0;
	RC_Ctrl.angley = 0;
	RC_Ctrl.anglez = 0;
}

#define USART_NRF_REC_LEN  			200  	//定义最大接收字节数 200

uint8_t  USART_NRF_RX_BUF[USART_NRF_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
uint16_t USART_NRF_RX_STA;         		  //接收状态标记

void usart_NRF_receive_data(uint8_t Res)
{
    if((USART_NRF_RX_STA&0x8000)==0)//接收未完成
    {
        if(Res== 0X3A)
        {
            USART_NRF_RX_STA|=0x8000;
            USART_NRF_RX_BUF[USART_NRF_RX_STA&0X3FFF]=Res ;
        }
        else
        {
            USART_NRF_RX_BUF[USART_NRF_RX_STA&0X3FFF]=Res ;
            USART_NRF_RX_STA++;
            if(USART_NRF_RX_STA>(USART_NRF_REC_LEN-1))USART_NRF_RX_STA=0;//接收数据错误,重新开始接收
        }
    }
}

//typedef union {
//	uint8_t uchar_data[4];
//	float   float_data;
//}uchar_to_float_t;

//uchar_to_float_t uchar_to_float;

void usart_NRF_receive_data_unpacket()
{
    if(USART_NRF_RX_STA&0x8000)
    {
		if(USART_NRF_RX_BUF[0] == 0xA3 && USART_NRF_RX_BUF[28] == 0X3A)
		{
			nrf_clean_flag = 1;
			RC_Ctrl.lx_value = (USART_NRF_RX_BUF[1]<<8) + USART_NRF_RX_BUF[2];
			RC_Ctrl.ly_value = (USART_NRF_RX_BUF[3]<<8) + USART_NRF_RX_BUF[4];
			RC_Ctrl.rx_value = (USART_NRF_RX_BUF[5]<<8) + USART_NRF_RX_BUF[6];
			RC_Ctrl.ry_value = (USART_NRF_RX_BUF[7]<<8) + USART_NRF_RX_BUF[8];
			
			RC_Ctrl.gyrox = (USART_NRF_RX_BUF[9]<<8) + USART_NRF_RX_BUF[10];
			RC_Ctrl.gyroy = (USART_NRF_RX_BUF[11]<<8) + USART_NRF_RX_BUF[12];
			RC_Ctrl.gyroz = (USART_NRF_RX_BUF[13]<<8) + USART_NRF_RX_BUF[14];
			
//			RC_Ctrl.accx = (USART_NRF_RX_BUF[15]<<8) + USART_NRF_RX_BUF[16];
//			RC_Ctrl.accy = (USART_NRF_RX_BUF[17]<<8) + USART_NRF_RX_BUF[18];
//			RC_Ctrl.accz = (USART_NRF_RX_BUF[19]<<8) + USART_NRF_RX_BUF[20];
			
			//RC_Ctrl.key_value = USART_NRF_RX_BUF[15];
			RC_Ctrl.KEY_YG_L = (USART_NRF_RX_BUF[15] >> 3)&0X01;
			RC_Ctrl.KEY_YG_R = (USART_NRF_RX_BUF[15] >> 2)&0X01;
			RC_Ctrl.KEY_BM_L = (USART_NRF_RX_BUF[15] >> 1)&0X01;
			RC_Ctrl.KEY_BM_R = (USART_NRF_RX_BUF[15] >> 0)&0X01;
			
			uchar_to_float.uchar_data[0] = USART_NRF_RX_BUF[16];
			uchar_to_float.uchar_data[1] = USART_NRF_RX_BUF[17];
			uchar_to_float.uchar_data[2] = USART_NRF_RX_BUF[18];
			uchar_to_float.uchar_data[3] = USART_NRF_RX_BUF[19];
			RC_Ctrl.anglex = uchar_to_float.float_data;
			
			uchar_to_float.uchar_data[0] = USART_NRF_RX_BUF[20];
			uchar_to_float.uchar_data[1] = USART_NRF_RX_BUF[21];
			uchar_to_float.uchar_data[2] = USART_NRF_RX_BUF[22];
			uchar_to_float.uchar_data[3] = USART_NRF_RX_BUF[23];
			RC_Ctrl.angley = uchar_to_float.float_data;
			
			uchar_to_float.uchar_data[0] = USART_NRF_RX_BUF[24];
			uchar_to_float.uchar_data[1] = USART_NRF_RX_BUF[25];
			uchar_to_float.uchar_data[2] = USART_NRF_RX_BUF[26];
			uchar_to_float.uchar_data[3] = USART_NRF_RX_BUF[27];
			RC_Ctrl.anglez = uchar_to_float.float_data;
			
		}
        memset(USART_NRF_RX_BUF,0,sizeof(USART_NRF_RX_BUF));
        USART_NRF_RX_STA=0;
    }
}

