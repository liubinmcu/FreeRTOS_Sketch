#include "app_task_main.h"
#include "app_task_queue.h"
#include "app_task_create.h"
#include "app_task_semphr.h"
#include "global_include.h"


#define TASK_START_STK_SIZE         128
#define TASK_QUEUE_START_STK_SIZE   128
#define TASK_CREATE_START_STK_SIZE  128
#define TASK_SEMPHR_START_STK_SIZE  128

#define TASK_START_PRIO         1
#define TASK_QUEUE_START_PRIO   2
#define TASK_CREATE_START_PRIO  3
#define TASK_SEMPHR_START_PRIO  4



TaskHandle_t xHandleTaskStart       = NULL;
TaskHandle_t xHandleTaskQueueStart  = NULL;
TaskHandle_t xHandleTaskCreateStart = NULL;
TaskHandle_t xHandletaskSemphrStart = NULL;


static void vTaskStart( void* pvParameters );

void app_task_create(void)
{
    xTaskCreate( vTaskStart,           /* ������  */
                 "vTaskStart",         /* ������    */
                 TASK_START_STK_SIZE,  /* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,                 /* �������  */
                 TASK_START_PRIO,      /* �������ȼ�*/
                 &xHandleTaskStart );  /* ������  */
}

static void vTaskStart( void* pvParameters )
{
//    xTaskCreate( vTaskQueueStart,
//                 "vTaskQueueStart",
//                 TASK_QUEUE_START_STK_SIZE,
//                 NULL,
//                 TASK_QUEUE_START_PRIO,
//                 &xHandleTaskQueueStart);
//    xTaskCreate( vTaskCreateStart,
//                 "vTaskCreateStart",
//                 TASK_CREATE_START_STK_SIZE,
//                 NULL,
//                 TASK_CREATE_START_PRIO,
//                 &xHandleTaskCreateStart);
    xTaskCreate( vTaskSemphrStart,
                 "vTaskSemphrStart",
                 TASK_SEMPHR_START_STK_SIZE,
                 NULL,
                 TASK_SEMPHR_START_PRIO,
                 &xHandletaskSemphrStart);

    vTaskDelete(xHandleTaskStart);
}

