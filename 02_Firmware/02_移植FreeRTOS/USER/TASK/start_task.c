/**
  ************************************************************************
  * @file       start_task.c/h
  * @brief      启动任务，将一个个任务开启，分配资源，给定任务优先级,
  ************************************************************************
**/
#include "start_task.h"

#include "user_task.h"

#define START_TASK_PRIO 1
#define START_STK_SIZE  128
static  TaskHandle_t    StartTask_Handler;

#define USER_TASK_PRIO 4
#define USER_STK_SIZE  512
static  TaskHandle_t   USERTask_Handler;

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区

    xTaskCreate((TaskFunction_t)user_task,          //任务函数
                (const char *)"user_task",          //任务名称
                (uint16_t)USER_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)USER_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&USERTask_Handler); //任务句柄
				
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

void startTask(void)
{
    xTaskCreate((TaskFunction_t)start_task,          //任务函数
                (const char *)"start_task",          //任务名称
                (uint16_t)START_STK_SIZE,            //任务堆栈大小
                (void *)NULL,                        //传递给任务函数的参数
                (UBaseType_t)START_TASK_PRIO,        //任务优先级
                (TaskHandle_t *)&StartTask_Handler); //任务句柄
}
