#include "app_task_eventgroup.h"
#include "global_include.h"

#define TASK_EVENTGROUPWAIT_STK_SIZE    128

#define TASK_EVENTGROUPWAIT_PRIO        13

#define EVENT_GROUP_BIT_0       (1<<0)
#define EVENT_GROUP_BIT_1       (1<<1)
#define EVENT_GROUP_BIT_2       (1<<2)
#define EVENT_GROUP_BIT_ALL     (EVENT_GROUP_BIT_0 | EVENT_GROUP_BIT_1 | EVENT_GROUP_BIT_2)



TimerHandle_t xHandleTimerAutoReloadForEventGroup = NULL;

TaskHandle_t xHandleTaskEventGroupWait = NULL;

EventGroupHandle_t xHandleEventGroup = NULL;

static void vTimerAutoReloadCallback( TimerHandle_t xTimer );
static void vTaskEventGroupWait( void* pvParameters );


void vTaskEventGroupStart( void* pvParameters )
{
    BaseType_t err;
    xHandleTimerAutoReloadForEventGroup = xTimerCreate("vTimerAutoReloadForEventGroup",
                                         1000,      //1000 1s
                                         pdTRUE,    //ÖÜÆÚ
                                         (void *)1,
                                        vTimerAutoReloadCallback);
    err = xTimerStart(xHandleTimerAutoReloadForEventGroup, 0);
    if(err == pdFALSE)
    {
        printf("vTimerAutoReloadForEventGroup Start Failed!!\r\n");
    }
    
    xHandleEventGroup = xEventGroupCreate();
    if(xHandleEventGroup == NULL)
    {
        printf("xHandleEventGroup Create Failed!!!\r\n");
    }
    xTaskCreate( vTaskEventGroupWait,
             "vTaskEventGroupWait",
             TASK_EVENTGROUPWAIT_STK_SIZE,
             NULL,
             TASK_EVENTGROUPWAIT_PRIO,
             &xHandleTaskEventGroupWait );

    vTaskDelete(NULL);
}

static void vTaskEventGroupWait( void* pvParameters )
{
    EventBits_t xEventValue;
    while(1)
    {
        if(xHandleEventGroup != NULL)
        {
            xEventValue = xEventGroupWaitBits(xHandleEventGroup, 
                                              EVENT_GROUP_BIT_ALL,
                                              pdTRUE,
                                              pdTRUE, 
                                              portMAX_DELAY);
            printf("All bits have set to 1 xEventValue = %#x\r\n", xEventValue);
        }
        
        vTaskDelay(1000);
    }
}


static void vTimerAutoReloadCallback( TimerHandle_t xTimer )
{
    static uint8_t count = 0;
    count++;
    if(count == 5)
    {
        xEventGroupSetBits(xHandleEventGroup, EVENT_GROUP_BIT_0);
    }
    else if(count == 10)
    {
        xEventGroupSetBits(xHandleEventGroup, EVENT_GROUP_BIT_1);
    }
    else if(count == 15)
    {
        xEventGroupSetBits(xHandleEventGroup, EVENT_GROUP_BIT_2);
    }

}


