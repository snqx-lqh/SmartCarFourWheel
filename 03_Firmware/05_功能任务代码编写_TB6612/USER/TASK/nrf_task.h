#ifndef _NRF_TASK_H
#define _NRF_TASK_H

#include "main.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

void nrf_task(void *pvParameters);

void usart_NRF_receive_data(uint8_t Res);
void usart_NRF_receive_data_unpacket(void);

typedef struct{
	uint16_t lx_value;
	uint16_t ly_value;
	uint16_t rx_value;
	uint16_t ry_value;
	
	int16_t gyrox;
	int16_t gyroy;
	int16_t gyroz;
	
	int16_t accx;
	int16_t accy;
	int16_t accz;
	
	//uint8_t key_value;
	uint8_t KEY_YG_L;
	uint8_t KEY_YG_R;
	uint8_t KEY_BM_L;
	uint8_t KEY_BM_R;
	
	
	float anglex;
	float angley;
	float anglez;
	
}RC_Ctrl_t;

extern RC_Ctrl_t RC_Ctrl;

#endif

