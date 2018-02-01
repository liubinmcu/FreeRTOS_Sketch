#include "app_task_queue.h"


#define TASK_QUEUE_SEND_MSG_STK_SIZE    256
#define TASK_QUEUE_RECEIVE_MSG_STK_SIZE 256

//优先级分配16-20
#define TASK_QUEUE_SEND_MSG_PRIO    17
#define TASK_QUEUE_RECEIVE_MSG_PRIO 16


#define QUEUE_MSG_SIZE  10

TaskHandle_t xHandleTaskQueueSendMsg = NULL;
TaskHandle_t xHandleTaskQueueReceiveMsg = NULL;

QueueHandle_t xHandleQueueMsg = NULL;


static void vTaskQueueSendMsg( void* pvParameters );
static void vTaskQueueReceiveMsg( void* pvParameters );


void vTaskQueueStart( void* pvParameters )
{
    printf("vTaskQueueStart running...\r\n");

    xHandleQueueMsg = xQueueCreate( QUEUE_MSG_SIZE, 10 );
    
    xTaskCreate( vTaskQueueSendMsg,
                 "vTaskQueueSendMsg",
                 TASK_QUEUE_SEND_MSG_STK_SIZE,
                 NULL,
                 TASK_QUEUE_SEND_MSG_PRIO,
                 &xHandleTaskQueueSendMsg );

//    xTaskCreate( vTaskQueueReceiveMsg,
//                 "vTaskQueueReceiveMsg",
//                 TASK_QUEUE_RECEIVE_MSG_STK_SIZE,
//                 NULL,
//                 TASK_QUEUE_RECEIVE_MSG_PRIO,
//                 &xHandleTaskQueueReceiveMsg );
    vTaskDelete(NULL);
}

static void vTaskQueueSendMsg( void* pvParameters )
{
    BaseType_t err = pdFALSE;
    char * sendstring = "liubin";
    while(1)
    {
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

static void vTaskQueueReceiveMsg( void* pvParameters )
{
    BaseType_t err = pdFALSE;
    uint8_t receive_buffer[10] = {0};
    while(1)
    {
        if(xHandleQueueMsg != NULL)
        {
            err = xQueueReceive( xHandleQueueMsg, receive_buffer, portMAX_DELAY );
            if(err == pdTRUE)
            {
                printf("receive data is: %s\r\n", receive_buffer);
            }
        }
        vTaskDelay( 500 );
    }

}



