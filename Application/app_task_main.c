#include "app_task_main.h"
#include "app_task_queue.h"
#include "app_task_create.h"
#include "app_task_semphr.h"
#include "app_task_statistics.h"
#include "app_task_softwaretimer.h"
#include "app_task_eventgroup.h"
#include "app_task_notification.h"
#include "app_task_memmang.h"
#include "global_include.h"


#define TASK_START_STK_SIZE                 128
#define TASK_QUEUE_START_STK_SIZE           128
#define TASK_CREATE_START_STK_SIZE          128
#define TASK_SEMPHR_START_STK_SIZE          128
#define TASK_STATISTICS_START_STK_SIZE      128
#define TASK_SOFTWARETIMER_START_STK_SIZE   128
#define TASK_EVENTGROUP_START_STK_SIZE      128
#define TASK_NOTIFICATION_START_STK_SIZE      128
#define TASK_MEMMANG_START_STK_SIZE      128


#define TASK_START_PRIO                 1
#define TASK_QUEUE_START_PRIO           2
#define TASK_CREATE_START_PRIO          3
#define TASK_SEMPHR_START_PRIO          4
#define TASK_STATISTICS_START_PRIO      5
#define TASK_SOFTWARETIMER_START_PRIO   6
#define TASK_EVENTGROUP_START_PRIO      7
#define TASK_NOTIFICATION_START_PRIO      8
#define TASK_MEMMANG_START_PRIO      9




TaskHandle_t xHandleTaskStart               = NULL;
TaskHandle_t xHandleTaskQueueStart          = NULL;
TaskHandle_t xHandleTaskCreateStart         = NULL;
TaskHandle_t xHandletaskSemphrStart         = NULL;
TaskHandle_t xHandletaskStatisticsStart     = NULL;
TaskHandle_t xHandletaskSoftwareTimerStart  = NULL;
TaskHandle_t xHandletaskEventGroupStart     = NULL;
TaskHandle_t xHandletaskNotificationStart     = NULL;
TaskHandle_t xHandletaskMemMangStart     = NULL;



static void vTaskStart( void* pvParameters );

void app_task_create(void)
{
    xTaskCreate( vTaskStart,           /* 任务函数  */
                 "vTaskStart",         /* 任务名    */
                 TASK_START_STK_SIZE,  /* 任务栈大小，单位word，也就是4字节 */
                 NULL,                 /* 任务参数  */
                 TASK_START_PRIO,      /* 任务优先级*/
                 &xHandleTaskStart );  /* 任务句柄  */
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
//    xTaskCreate( vTaskSemphrStart,
//                 "vTaskSemphrStart",
//                 TASK_SEMPHR_START_STK_SIZE,
//                 NULL,
//                 TASK_SEMPHR_START_PRIO,
//                 &xHandletaskSemphrStart);
//    xTaskCreate( vTaskStatisticsStart,
//                 "vTaskStatisticsStart",
//                 TASK_STATISTICS_START_STK_SIZE,
//                 NULL,
//                 TASK_STATISTICS_START_PRIO,
//                 &xHandletaskStatisticsStart);
//    xTaskCreate( vTaskSoftwareTimerStart,
//                 "vTaskSoftwareTimerStart",
//                 TASK_SOFTWARETIMER_START_STK_SIZE,
//                 NULL,
//                 TASK_SOFTWARETIMER_START_PRIO,
//                 &xHandletaskSoftwareTimerStart);
//    xTaskCreate( vTaskEventGroupStart,
//                 "vTaskEventGroupStart",
//                 TASK_EVENTGROUP_START_STK_SIZE,
//                 NULL,
//                 TASK_EVENTGROUP_START_PRIO,
//                 &xHandletaskEventGroupStart);
    xTaskCreate( vTaskNotificationStart,
                 "vTaskNotificationStart",
                 TASK_NOTIFICATION_START_STK_SIZE,
                 NULL,
                 TASK_NOTIFICATION_START_PRIO,
                 &xHandletaskNotificationStart);
//    xTaskCreate( vTaskMemMangStart,
//                 "vTaskMemMangStart",
//                 TASK_MEMMANG_START_STK_SIZE,
//                 NULL,
//                 TASK_MEMMANG_START_PRIO,
//                 &xHandletaskMemMangStart);


    vTaskDelete(xHandleTaskStart);
}


