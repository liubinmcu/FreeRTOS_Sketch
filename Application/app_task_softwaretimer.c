#include "app_task_softwaretimer.h"
#include "FreeRTOS.h"
#include "timers.h"

TimerHandle_t xHandleTimerAutoReload = NULL;
TimerHandle_t xHandleTimerOneShot = NULL;

static void vTimerAutoReloadCallback( TimerHandle_t xTimer );
static void vTimerOneShotCallback( TimerHandle_t xTimer );


void vTaskSoftwareTimerStart( void* pvParameters )
{
    BaseType_t err;
    xHandleTimerAutoReload = xTimerCreate("vTimerAutoReload",
                                         1000,      //1000 1s
                                         pdTRUE,    //周期
                                         (void *)1,
                                        vTimerAutoReloadCallback);
     
    xHandleTimerOneShot = xTimerCreate("vTimerOneShot",
                                       2000,        //2000 2s
                                       pdFALSE,     //单次
                                       (void *)2,
                                       vTimerOneShotCallback);
    err = xTimerStart(xHandleTimerAutoReload, 0);
    if(err == pdFALSE)
    {
        printf("AutoReloadTimer Start Failed!!\r\n");
    }
    vTaskDelete(NULL);
}

static void vTimerAutoReloadCallback( TimerHandle_t xTimer )
{
    static uint8_t count = 0;
    BaseType_t err;
    printf("vTimerAutoReloadCallback running %d!!!\r\n", ++count);
    if(count % 5 == 0)
    {
        err = xTimerStart(xHandleTimerOneShot, 0);
        if(err == pdFALSE)
        {
            printf("OneShotTimer Start Failed!!\r\n");
        }
    }
    if(count == 20)
    {
        err = xTimerStop(xHandleTimerAutoReload, 0);
        if(err == pdFALSE)
        {
            printf("AutoReloadTimer Stop Failed!!\r\n");
        }
    }
}

static void vTimerOneShotCallback( TimerHandle_t xTimer )
{
    static uint8_t count = 0;
    printf("vTimerOneShotCallback running %d!!!\r\n", ++count);
}


