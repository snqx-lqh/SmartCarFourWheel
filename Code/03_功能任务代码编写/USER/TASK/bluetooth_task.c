#include "bluetooth_task.h"

#include "bluetooth_debugger.h"
#include "bsp_usart.h"

void bluetooth_task(void *pvParameters)
{
	
	while(1)
	{
		tx_pack_ptr.bools[0] = rx_pack_ptr.bools[0];
		tx_pack_ptr.bools[1] = rx_pack_ptr.bools[1];
		tx_pack_ptr.bytes[0] = rx_pack_ptr.bytes[0];
		tx_pack_ptr.shorts[0] = rx_pack_ptr.shorts[0]; 
		tx_pack_ptr.shorts[1] = rx_pack_ptr.shorts[1]; 
		tx_pack_ptr.integers[0] = rx_pack_ptr.integers[0]; 
		tx_pack_ptr.floats[0] = rx_pack_ptr.floats[0];
		data_send_packet(&tx_pack_ptr,usart_tx_buff);
		usart2_send_array(usart_tx_buff,17);
		vTaskDelay(50);
	}
}
