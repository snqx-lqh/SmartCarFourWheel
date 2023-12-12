/**
  ************************************************************************
  * @file       start_task.c/h
  * @brief      �������񣬽�һ������������������Դ�������������ȼ�,
  ************************************************************************
**/
#include "start_task.h"

#include "user_task.h"
#include "bluetooth_task.h"
#include "chassis_task.h"

#define START_TASK_PRIO 1
#define START_STK_SIZE  128
static  TaskHandle_t    StartTask_Handler;

#define USER_TASK_PRIO 4
#define USER_STK_SIZE  512
static  TaskHandle_t   USERTask_Handler;

#define BLUETOOTH_TASK_PRIO 5
#define BLUETOOTH_STK_SIZE  512
static  TaskHandle_t   BLUETOOTHTask_Handler;

#define CHASSIS_TASK_PRIO 6
#define CHASSIS_STK_SIZE  512
static  TaskHandle_t   CHASSISTask_Handler;

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���

    xTaskCreate((TaskFunction_t)user_task,          //������
                (const char *)"user_task",          //��������
                (uint16_t)USER_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)USER_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&USERTask_Handler); //������

	xTaskCreate((TaskFunction_t)bluetooth_task,          //������
                (const char *)"bluetooth_task",          //��������
                (uint16_t)BLUETOOTH_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)BLUETOOTH_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&BLUETOOTHTask_Handler); //������
	
	xTaskCreate((TaskFunction_t)chassis_task,          //������
                (const char *)"chassis_task",          //��������
                (uint16_t)CHASSIS_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)CHASSIS_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&CHASSISTask_Handler); //������
				
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

void startTask(void)
{
    xTaskCreate((TaskFunction_t)start_task,          //������
                (const char *)"start_task",          //��������
                (uint16_t)START_STK_SIZE,            //�����ջ��С
                (void *)NULL,                        //���ݸ��������Ĳ���
                (UBaseType_t)START_TASK_PRIO,        //�������ȼ�
                (TaskHandle_t *)&StartTask_Handler); //������
}
