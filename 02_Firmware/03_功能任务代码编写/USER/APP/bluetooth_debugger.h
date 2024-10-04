/**
  ************************************* Copyright ****************************** 
  *
  *                 (C) Copyright 2023,LQH,China, GCU.
  *                            All Rights Reserved
  *                              
  *                                  By LQH
  *                     
  *    
  * FileName   : bluetooth_debugger.h   		
  * Author     : ����Ǳ��(snqx-lgh)			
  * Date       : 2023-11-03         
  * Description: CSDN��ҳ�� https://blog.csdn.net/wan1234512?type=blog
			     Gitee��ַ��https://gitee.com/snqx-lqh  
				 �ο����ӣ� https://blog.csdn.net/m0_51220742/article/details/123880490
  ******************************************************************************
 */

#ifndef __BLUETOOTH_DEBUGGER_H_
#define __BLUETOOTH_DEBUGGER_H_

#include "main.h"

#define RX_DATA_NUM  100
#define TX_DATA_NUM  100
// ָ�����͵��ֻ������ݰ��Ľṹ
// ����ʵ����Ҫ�ı������������ݰ��� bool byte short int float �������͵���Ŀ

#define TX_BOOL_NUM 2
#define TX_BYTE_NUM 1
#define TX_SHORT_NUM 2
#define TX_INT_NUM 1
#define TX_FLOAT_NUM 1

// ָ���������ݰ��Ľṹ
// ����ʵ����Ҫ�ı������������ݰ��� bool byte short int float �������͵���Ŀ

#define RX_BOOL_NUM 2
#define RX_BYTE_NUM 1
#define RX_SHORT_NUM 2
#define RX_INT_NUM 1
#define RX_FLOAT_NUM 1

typedef struct
{
#if TX_BOOL_NUM > 0
	unsigned char bools[TX_BOOL_NUM];
#endif

#if TX_BYTE_NUM > 0
	char bytes[TX_BYTE_NUM];
#endif

#if TX_SHORT_NUM > 0
	short shorts[TX_SHORT_NUM];
#endif

#if TX_INT_NUM > 0
	int integers[TX_INT_NUM];
#endif

#if TX_FLOAT_NUM > 0
	float floats[TX_FLOAT_NUM];
#endif
	char space; // �����壬ֻΪ�˲��ýṹ��Ϊ�գ��ṹ��Ϊ�ջᱨ��
} TxPack;

typedef struct
{
#if RX_BOOL_NUM > 0
	unsigned char bools[RX_BOOL_NUM];
#endif

#if RX_BYTE_NUM > 0
	char bytes[RX_BYTE_NUM];
#endif

#if RX_SHORT_NUM > 0
	short shorts[RX_SHORT_NUM];
#endif

#if RX_INT_NUM > 0
	int integers[RX_INT_NUM];
#endif

#if RX_FLOAT_NUM > 0
	float floats[RX_FLOAT_NUM];
#endif
	char space; // �����壬ֻΪ�˲��ýṹ��Ϊ�գ��ṹ��Ϊ�ջᱨ��
} RxPack;

typedef union {
	uint8_t uchar_data[4];
	float   float_data;
}uchar_to_float_t;


//���ڽ�������
void get_usart_data(uint8_t rx_buff,uint8_t *usart_rx_buff);
// �������ݰ�
void data_unpacket(RxPack *rx_pack_ptr,uint8_t *usart_rx_buff);
// �������ݰ�
void data_send_packet(TxPack *tx_pack_ptr,uint8_t *usart_tx_buff);

extern RxPack rx_pack_ptr;
extern TxPack tx_pack_ptr;
extern uint8_t usart_rx_buff[];
extern uint8_t usart_tx_buff[];

#define PACK_HEAD 0xa5
#define PACK_TAIL 0x5a

#endif

