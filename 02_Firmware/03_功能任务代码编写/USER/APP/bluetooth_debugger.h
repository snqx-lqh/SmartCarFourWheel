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
  * Author     : 少年潜行(snqx-lgh)			
  * Date       : 2023-11-03         
  * Description: CSDN主页： https://blog.csdn.net/wan1234512?type=blog
			     Gitee地址：https://gitee.com/snqx-lqh  
				 参考链接： https://blog.csdn.net/m0_51220742/article/details/123880490
  ******************************************************************************
 */

#ifndef __BLUETOOTH_DEBUGGER_H_
#define __BLUETOOTH_DEBUGGER_H_

#include "main.h"

#define RX_DATA_NUM  100
#define TX_DATA_NUM  100
// 指定发送到手机的数据包的结构
// 根据实际需要的变量，定义数据包中 bool byte short int float 五种类型的数目

#define TX_BOOL_NUM 2
#define TX_BYTE_NUM 1
#define TX_SHORT_NUM 2
#define TX_INT_NUM 1
#define TX_FLOAT_NUM 1

// 指定接收数据包的结构
// 根据实际需要的变量，定义数据包中 bool byte short int float 五种类型的数目

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
	char space; // 无意义，只为了不让结构体为空，结构体为空会报错。
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
	char space; // 无意义，只为了不让结构体为空，结构体为空会报错。
} RxPack;

typedef union {
	uint8_t uchar_data[4];
	float   float_data;
}uchar_to_float_t;


//串口接受数据
void get_usart_data(uint8_t rx_buff,uint8_t *usart_rx_buff);
// 解析数据包
void data_unpacket(RxPack *rx_pack_ptr,uint8_t *usart_rx_buff);
// 发送数据包
void data_send_packet(TxPack *tx_pack_ptr,uint8_t *usart_tx_buff);

extern RxPack rx_pack_ptr;
extern TxPack tx_pack_ptr;
extern uint8_t usart_rx_buff[];
extern uint8_t usart_tx_buff[];

#define PACK_HEAD 0xa5
#define PACK_TAIL 0x5a

#endif

