/**
  ************************************* Copyright ****************************** 
  *
  *                 (C) Copyright 2023,LQH,China, GCU.
  *                            All Rights Reserved
  *                              
  *                                  By LQH
  *                     
  *    
  * FileName   : bluetooth_debugger.c   		
  * Author     : 少年潜行(snqx-lgh)			
  * Date       : 2023-11-03         
  * Description: CSDN主页： https://blog.csdn.net/wan1234512?type=blog
			     Gitee地址：https://gitee.com/snqx-lqh   
				 参考链接： https://blog.csdn.net/m0_51220742/article/details/123880490
  ******************************************************************************
 */
#include "bluetooth_debugger.h"

RxPack rx_pack_ptr;
TxPack tx_pack_ptr;
uint8_t usart_rx_buff[RX_DATA_NUM];
uint8_t usart_tx_buff[TX_DATA_NUM];
uchar_to_float_t uchar_to_float;

void get_usart_data(uint8_t rx_buff,uint8_t *usart_rx_buff)
{
	static uint8_t data_count = 0;
	if(rx_buff == PACK_HEAD)
	{
		usart_rx_buff[0] = rx_buff;
		data_count ++;
	}else if(data_count > 0)
	{
		usart_rx_buff[data_count] = rx_buff;
		data_count ++;
		if(rx_buff == PACK_TAIL)
		{
			data_count = 0;		
		}
	}
}

// 解析数据包
void data_unpacket(RxPack *rx_pack_ptr,uint8_t *usart_rx_buff)
{
	uint8_t i;
	uint8_t data_num = 0;
	uint8_t check_num = 0;
	uint8_t addr_offest = 0;
	data_num = 3 + RX_BOOL_NUM/8+1 + RX_BYTE_NUM + RX_SHORT_NUM*2 + RX_INT_NUM*4 + RX_FLOAT_NUM*4;
	if(usart_rx_buff[0] == PACK_HEAD && usart_rx_buff[data_num-1] == PACK_TAIL)
	{
		for(i=0;i<(data_num-3);i++)
		{
			check_num += usart_rx_buff[i+1];
		}
		if(check_num == usart_rx_buff[data_num-2])
		{
			addr_offest += 1;
			#if RX_BOOL_NUM > 0
				for(i=0;i<RX_BOOL_NUM;i++)
				{
					rx_pack_ptr->bools[i] = (usart_rx_buff[addr_offest+i/8]>>(i%8))&0x01;
				}
			#endif
				
			addr_offest += RX_BOOL_NUM/8+1;
			#if RX_BYTE_NUM > 0
				for(i=0;i<RX_BYTE_NUM;i++)
				{
					rx_pack_ptr->bytes[i] = usart_rx_buff[addr_offest+i];
				}
			#endif
			
			addr_offest += RX_BYTE_NUM;
			#if RX_SHORT_NUM > 0
				for(i=0;i<RX_SHORT_NUM;i++)
				{
					rx_pack_ptr->shorts[i] = (usart_rx_buff[addr_offest+i*2+1] << 8) + usart_rx_buff[addr_offest+i*2];
				}
			#endif
				
			addr_offest += RX_SHORT_NUM*2;
			#if RX_INT_NUM > 0
				for(i=0;i<RX_INT_NUM;i++)
				{
					rx_pack_ptr->integers[i] =  (usart_rx_buff[addr_offest+i*4+3] << 24) + \
												(usart_rx_buff[addr_offest+i*4+2] << 16) + \
												(usart_rx_buff[addr_offest+i*4+1] << 8)  + \
												 usart_rx_buff[addr_offest+i*4];
				}
			#endif
				
			addr_offest += RX_INT_NUM*4;
			#if RX_FLOAT_NUM > 0
				for(i=0;i<RX_FLOAT_NUM;i++)
				{
					uchar_to_float.uchar_data[3] = usart_rx_buff[addr_offest+i*4+3];
					uchar_to_float.uchar_data[2] = usart_rx_buff[addr_offest+i*4+2];
					uchar_to_float.uchar_data[1] = usart_rx_buff[addr_offest+i*4+1];
					uchar_to_float.uchar_data[0] = usart_rx_buff[addr_offest+i*4];
					rx_pack_ptr->floats[i] = uchar_to_float.float_data;
				}
			#endif
		}
	}
	
}
// 发送数据包
void data_send_packet(TxPack *tx_pack_ptr,uint8_t *usart_tx_buff)
{
	uint8_t i;
	uint8_t data_num = 0;
	uint8_t check_num = 0;
	uint8_t addr_offest = 0;
	data_num = 3 + TX_BOOL_NUM/8+1 + TX_BYTE_NUM + TX_SHORT_NUM*2 + TX_INT_NUM*4 + TX_FLOAT_NUM*4;
	
	usart_tx_buff[0] = PACK_HEAD;
	usart_tx_buff[data_num-1] = PACK_TAIL;
	
	addr_offest += 1;
	#if TX_BOOL_NUM > 0
		for(i=0;i<TX_BOOL_NUM;i++)
		{
			usart_tx_buff[addr_offest+i/8] = 0x00;
		}
		for(i=0;i<TX_BOOL_NUM;i++)
		{
			usart_tx_buff[addr_offest+i/8] <<= 1;
			usart_tx_buff[addr_offest+i/8]|=tx_pack_ptr->bools[TX_BOOL_NUM - 1 - i];
		}
	#endif
		
	addr_offest += TX_BOOL_NUM/8+1;
	#if TX_BYTE_NUM > 0
		for(i=0;i<TX_BYTE_NUM;i++)
		{
			usart_tx_buff[addr_offest+i] = tx_pack_ptr->bytes[i];
		}
	#endif
	
	addr_offest += TX_BYTE_NUM;
	#if TX_SHORT_NUM > 0
		for(i=0;i<TX_SHORT_NUM;i++)
		{
			usart_tx_buff[addr_offest+i*2+1] = tx_pack_ptr->shorts[i] >> 8;
			usart_tx_buff[addr_offest+i*2]   = tx_pack_ptr->shorts[i];
		}
	#endif
		
	addr_offest += TX_SHORT_NUM*2;
	#if TX_INT_NUM > 0
		for(i=0;i<TX_INT_NUM;i++)
		{
			usart_tx_buff[addr_offest+i*4+3] = tx_pack_ptr->integers[i] >>24;
			usart_tx_buff[addr_offest+i*4+2] = tx_pack_ptr->integers[i] >>16;
			usart_tx_buff[addr_offest+i*4+1] = tx_pack_ptr->integers[i] >>8;
			usart_tx_buff[addr_offest+i*4+0] = tx_pack_ptr->integers[i] ;
		}
	#endif
		
	addr_offest += TX_INT_NUM*4;
	#if TX_FLOAT_NUM > 0
		for(i=0;i<TX_FLOAT_NUM;i++)
		{
			uchar_to_float.float_data = tx_pack_ptr->floats[i];
			usart_tx_buff[addr_offest+i*4+3] = uchar_to_float.uchar_data[3] ;
			usart_tx_buff[addr_offest+i*4+2] = uchar_to_float.uchar_data[2] ;
			usart_tx_buff[addr_offest+i*4+1] = uchar_to_float.uchar_data[1] ;
			usart_tx_buff[addr_offest+i*4]   = uchar_to_float.uchar_data[0] ;
		}
	#endif
	for(i=0;i<(data_num-3);i++)
	{
		check_num += usart_tx_buff[i+1];
	}
	usart_tx_buff[data_num-2] = check_num;
}

