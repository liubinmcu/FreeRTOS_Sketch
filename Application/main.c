#include "bsp_hardware.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define TASK_START_STK_SIZE 128
#define TASK_LED_STK_SIZE   512
#define TASK_PRINT_STK_SIZE 512
#define TASK_MSG_STK_SIZE   512


#define TASK_START_PRIO 1
#define TASK_LED_PRIO   2
#define TASK_PRINT_PRIO 3
#define TASK_MSG_PRIO   4

#define QUEUE_MSG_SIZE  10


static void AppTaskCreate( void );
static void vTaskStart( void* pvParameters );
static void vTaskLED( void* pvParameters );
static void vTaskPrint( void* pvParameters );
static void vTaskMsg( void* pvParameters );


/*
**********************************************************************************************************
                                            变量声明
**********************************************************************************************************
*/
TaskHandle_t xHandleTaskStart = NULL;
TaskHandle_t xHandleTaskLED = NULL;
TaskHandle_t xHandleTaskPrint = NULL;
TaskHandle_t xHandleTaskMsg = NULL;

QueueHandle_t xHandleQueueMsg = NULL;


void main( void )
{
    printf( "FreeRTOS_Sketch Start......\r\n" );
    bsp_hardware_init();
    /* 创建任务 */
    AppTaskCreate();
    /* 启动调度，开始执行任务 */
    vTaskStartScheduler();
    while( 1 )
    {
      
    }
}

static void AppTaskCreate(void)
{
    xTaskCreate( vTaskStart,       /* 任务函数  */
                 "vTaskStart",         /* 任务名    */
                 TASK_START_STK_SIZE,                   /* 任务栈大小，单位word，也就是4字节 */
                 NULL,                  /* 任务参数  */
                 TASK_START_PRIO,                     /* 任务优先级*/
                 &xHandleTaskStart );  /* 任务句柄  */
}

static void vTaskStart( void* pvParameters )
{
    xHandleQueueMsg = xQueueCreate( QUEUE_MSG_SIZE, 10 );


    xTaskCreate( vTaskLED,       /* 任务函数  */
                 "vTaskLED",         /* 任务名    */
                 TASK_LED_STK_SIZE,                   /* 任务栈大小，单位word，也就是4字节 */
                 NULL,                  /* 任务参数  */
                 TASK_LED_PRIO,                     /* 任务优先级*/
                 & xHandleTaskLED);  /* 任务句柄  */
    xTaskCreate( vTaskPrint,          /* 任务函数  */
                 "vTaskPrint",        /* 任务名    */
                 TASK_PRINT_STK_SIZE,               /* 任务栈大小，单位word，也就是4字节 */
                 NULL,              /* 任务参数  */
                 TASK_PRINT_PRIO,                 /* 任务优先级*/
                 &xHandleTaskPrint ); /* 任务句柄  */
    xTaskCreate( vTaskMsg,          /* 任务函数  */
             "vTaskMsg",        /* 任务名    */
             TASK_MSG_STK_SIZE,               /* 任务栈大小，单位word，也就是4字节 */
             NULL,              /* 任务参数  */
             TASK_MSG_PRIO,                 /* 任务优先级*/
             &xHandleTaskMsg ); /* 任务句柄  */
    vTaskDelete(xHandleTaskStart);
}

static void vTaskLED( void* pvParameters )
{
    static uint8_t count = 0;
    BaseType_t err = pdFALSE;
    char * sendstring = "roubin";
    while( 1 )
    {
        count++;
//        printf( "vTaskLED start %d\r\n", count);
//        if(count == 5)
//        {
//            vTaskDelete(xHandleTaskPrint);
//        }
//        else if(count == 10)
//        {
//            vTaskDelete(xHandleTaskMsg);
//        }
//        else if(count == 15)
//        {
//            vTaskDelete(xHandleTaskLED);
//        }
        if(xHandleQueueMsg != NULL)
        {
            err = xQueueSend( xHandleQueueMsg, sendstring, 10 );
            if(err == pdTRUE)
            {
                printf("data send successful \r\n");
            }
        }
        vTaskDelay( 800 );
    }
}

static void vTaskPrint( void* pvParameters )
{
//    static float float_num = 0.00;
//    uint8_t receive_data = 0;
    while( 1 )
    {
//        float_num += 0.01f;
//        printf( "float_num的值为: %.4f\r\n", float_num );
//         if(xQueueReceive( xHandleQueueMsg, &receive_data, portMAX_DELAY ))
//         {
//            printf("receive data is %d\r\n", receive_data);
//         }
        vTaskDelay( 100 );
    }
}

static void vTaskMsg( void* pvParameters )
{
    while( 1 )
    {
//        printf( "vTaskMsg start\r\n");
        vTaskDelay( 500 );
    }
}



