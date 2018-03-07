#include "app_task_memmang.h"
#include "global_include.h"

TimerHandle_t xHandleMemMangTimerAutoReload = NULL;

static void vTimerAutoReloadCallback( TimerHandle_t xTimer );

uint8_t *buffer = NULL;

void vTaskMemMangStart( void* pvParameters )
{
    BaseType_t err;
    xHandleMemMangTimerAutoReload = xTimerCreate("vTimerAutoReload",
                                         1000,      //1000 1s
                                         pdTRUE,    //ÖÜÆÚ
                                         (void *)1,
                                        vTimerAutoReloadCallback);
    err = xTimerStart(xHandleMemMangTimerAutoReload, 0);
    if(err == pdFALSE)
    {
        printf("AutoReloadTimer Start Failed!!\r\n");
    }
    vTaskDelete(NULL);
}

static void vTimerAutoReloadCallback( TimerHandle_t xTimer )
{
    static uint8_t count = 0;
    uint32_t freemem = 0;
    printf("vTimerAutoReloadCallback running %d!!!\r\n", ++count);
    if(count == 5)
    {
        freemem = xPortGetFreeHeapSize();
        printf("before malloc->free memery size = %d\r\n", freemem);
        buffer = pvPortMalloc(50);
        printf("malloc memery address = %#x\r\n", buffer);
        freemem = xPortGetFreeHeapSize();
        printf("after malloc->free memery size = %d\r\n", freemem);
    }
    if(count == 10)
    {
        if(buffer != NULL)
        {
          sprintf((char *)buffer, "use times = %d", count);
          printf("buffer = %s\r\n", buffer);
        }
    }
    if(count == 15)
    {
        if(buffer != NULL)
        {
            vPortFree(buffer);
            buffer = NULL;
            freemem = xPortGetFreeHeapSize();
            printf("after free->free memery size = %d\r\n", freemem);
            printf("free memery address = %#x\r\n", buffer);
        }
        
    }
}