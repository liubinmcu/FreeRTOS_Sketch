#include "app_task_semphr.h"
#include "global_include.h"

#define TEST_BINARY_SEMAPHORE   0
#define TEST_COUNTING_SEMAPHORE 0
#define TEST_PRIORITY_INVERSION 1
#define TEST_MUTEX_SEMAPHORE    0

#define TASK_SEMPHR_BINARY_TAKE_STK_SIZE     256
#define TASK_SEMPHR_BINARY_GIVE_STK_SIZE     256
#define TASK_SEMPHR_COUNTING_TAKE_STK_SIZE   256
#define TASK_SEMPHR_COUNTING_GIVE_STK_SIZE   256
#define TASK_PRIORITY_LOW_STK_SIZE           256
#define TASK_PRIORITY_MEDIUM_STK_SIZE        256
#define TASK_PRIORITY_HIGH_STK_SIZE          256
#define TASK_PRIORITY_MUTEX_LOW_STK_SIZE           256
#define TASK_PRIORITY_MUTEX_MEDIUM_STK_SIZE        256
#define TASK_PRIORITY_MUTEX_HIGH_STK_SIZE          256

#define TASK_SEMPHR_BINARY_TAKE_PRIO     21
#define TASK_SEMPHR_BINARY_GIVE_PRIO     22
#define TASK_SEMPHR_COUNTING_TAKE_PRIO   23
#define TASK_SEMPHR_COUNTING_GIVE_PRIO   24
#define TASK_PRIORITY_LOW_PRIO           25
#define TASK_PRIORITY_MEDIUM_PRIO        26
#define TASK_PRIORITY_HIGH_PRIO          27
#define TASK_PRIORITY_MUTEX_LOW_PRIO           28
#define TASK_PRIORITY_MUTEX_MEDIUM_PRIO        29
#define TASK_PRIORITY_MUTEX_HIGH_PRIO          30

TaskHandle_t xHandleTaskSemphrBinaryTake = NULL;
TaskHandle_t xHandleTaskSemphrBinaryGive = NULL;
TaskHandle_t xHandleTaskSemphrCountingTake = NULL;
TaskHandle_t xHandleTaskSemphrCountingGive = NULL;
TaskHandle_t xHandleTaskPriorityLow     = NULL;
TaskHandle_t xHandleTaskPriorityMedium  = NULL;
TaskHandle_t xHandleTaskPriorityHigh    = NULL;
TaskHandle_t xHandleTaskMutexPriorityLow     = NULL;
TaskHandle_t xHandleTaskMutexPriorityMedium  = NULL;
TaskHandle_t xHandleTaskMutexPriorityHigh    = NULL;

SemaphoreHandle_t xHandleSemphrBinary    = NULL;
SemaphoreHandle_t xHandleSemphrCounting  = NULL;
SemaphoreHandle_t xHandleSemphrPrioInversion  = NULL;
SemaphoreHandle_t xHandleSemphrMutex  = NULL;

static void vTaskSemphrBinaryTake( void* pvParameters );
static void vTaskSemphrBinaryGive( void* pvParameters );
static void vTaskSemphrCountingTake( void* pvParameters );
static void vTaskSemphrCountingGive( void* pvParameters );
static void vTaskPriorityLow( void* pvParameters );
static void vTaskPriorityMedium( void* pvParameters );
static void vTaskPriorityHigh( void* pvParameters );
static void vTaskMutexPriorityLow( void* pvParameters );
static void vTaskMutexPriorityMedium( void* pvParameters );
static void vTaskMutexPriorityHigh( void* pvParameters );

void vTaskSemphrStart( void* pvParameters )
{
    printf("vTaskSemphrStart running...\r\n");
    xHandleSemphrBinary = xSemaphoreCreateBinary();
    xHandleSemphrCounting = xSemaphoreCreateCounting(100, 0);
    xHandleSemphrPrioInversion = xSemaphoreCreateBinary();
    xHandleSemphrMutex = xSemaphoreCreateMutex();
    if(xHandleSemphrPrioInversion != NULL)
    {
        xSemaphoreGive(xHandleSemphrPrioInversion);
    }
    else
    {
        printf("create priority inversion semaphore failed!!!\r\n");
    }
    if(xHandleSemphrMutex != NULL)
    {
        xSemaphoreGive(xHandleSemphrMutex);
    }
    else
    {
        printf("create mutex semaphore failed!!!\r\n");
    }
#if (TEST_BINARY_SEMAPHORE == 1)
    xHandleSemphrBinary = xSemaphoreCreateBinary();
    xTaskCreate( vTaskSemphrBinaryTake,
                 "vTaskSemphrBinaryTake",
                 TASK_SEMPHR_BINARY_TAKE_STK_SIZE,
                 NULL,
                 TASK_SEMPHR_BINARY_TAKE_PRIO,
                 &xHandleTaskSemphrBinaryTake );
                 
    xTaskCreate( vTaskSemphrBinaryGive,
                 "vTaskSemphrBinaryGive",
                 TASK_SEMPHR_BINARY_GIVE_STK_SIZE,
                 NULL,
                 TASK_SEMPHR_BINARY_GIVE_PRIO,
                 &xHandleTaskSemphrBinaryGive );
#endif

#if(TEST_COUNTING_SEMAPHORE == 1)
    xHandleSemphrCounting = xSemaphoreCreateCounting(100, 0);
    xTaskCreate( vTaskSemphrCountingTake,
                 "vTaskSemphrCountingTake",
                 TASK_SEMPHR_COUNTING_TAKE_STK_SIZE,
                 NULL,
                 TASK_SEMPHR_COUNTING_TAKE_PRIO,
                 &xHandleTaskSemphrCountingTake );
                 
    xTaskCreate( vTaskSemphrCountingGive,
                 "vTaskSemphrCountingGive",
                 TASK_SEMPHR_COUNTING_GIVE_STK_SIZE,
                 NULL,
                 TASK_SEMPHR_COUNTING_GIVE_PRIO,
                 &xHandleTaskSemphrCountingGive );
#endif

#if(TEST_PRIORITY_INVERSION == 1)
    xHandleSemphrPrioInversion = xSemaphoreCreateBinary();
    if(xHandleSemphrPrioInversion != NULL)
    {
        xSemaphoreGive(xHandleSemphrPrioInversion);
    }
    else
    {
        printf("create priority inversion semaphore failed!!!\r\n");
    }
    xTaskCreate( vTaskPriorityHigh,
                 "vTaskPriorityHigh",
                 TASK_PRIORITY_HIGH_STK_SIZE,
                 NULL,
                 TASK_PRIORITY_HIGH_PRIO,
                 &xHandleTaskPriorityHigh );
    xTaskCreate( vTaskPriorityLow,
                 "vTaskPriorityLow",
                 TASK_PRIORITY_LOW_STK_SIZE,
                 NULL,
                 TASK_PRIORITY_LOW_PRIO,
                 &xHandleTaskPriorityLow );
    xTaskCreate( vTaskPriorityMedium,
                 "vTaskPriorityMedium",
                 TASK_PRIORITY_MEDIUM_STK_SIZE,
                 NULL,
                 TASK_PRIORITY_MEDIUM_PRIO,
                 &xHandleTaskPriorityMedium );
#endif

#if(TEST_MUTEX_SEMAPHORE == 1)
    xHandleSemphrMutex = xSemaphoreCreateMutex();
    if(xHandleSemphrMutex != NULL)
    {
        xSemaphoreGive(xHandleSemphrMutex);
    }
    else
    {
        printf("create mutex semaphore failed!!!\r\n");
    }
    xTaskCreate( vTaskMutexPriorityHigh,
                 "vTaskMutexPriorityHigh",
                 TASK_PRIORITY_MUTEX_HIGH_STK_SIZE,
                 NULL,
                 TASK_PRIORITY_MUTEX_HIGH_PRIO,
                 &xHandleTaskMutexPriorityHigh );
    xTaskCreate( vTaskMutexPriorityLow,
                 "vTaskMutexPriorityLow",
                 TASK_PRIORITY_MUTEX_LOW_STK_SIZE,
                 NULL,
                 TASK_PRIORITY_MUTEX_LOW_PRIO,
                 &xHandleTaskMutexPriorityLow );
    xTaskCreate( vTaskMutexPriorityMedium,
                 "vTaskMutexPriorityMedium",
                 TASK_PRIORITY_MUTEX_MEDIUM_STK_SIZE,
                 NULL,
                 TASK_PRIORITY_MUTEX_MEDIUM_PRIO,
                 &xHandleTaskMutexPriorityMedium );
#endif

    vTaskDelete(NULL);
}

//binary semphore test
static void vTaskSemphrBinaryTake( void* pvParameters )
{
    BaseType_t err;
    while(1)
    {
        if(xHandleSemphrBinary != NULL)
        {
            err = xSemaphoreTake(xHandleSemphrBinary, portMAX_DELAY);
            if(err == pdTRUE)
            {
                printf("receive binary semphore...\r\n");
            }
        }
        vTaskDelay(500);
    }
}

static void vTaskSemphrBinaryGive( void* pvParameters )
{
    BaseType_t err;
    while(1)
    {
        if(xHandleSemphrBinary != NULL)
        {
            err = xSemaphoreGive(xHandleSemphrBinary);
            if(err == pdTRUE)
            {
                printf("binary semphore give successful...\r\n");
            }
        }
        vTaskDelay(1000);
    }
}

//counting semphore test
static void vTaskSemphrCountingTake( void* pvParameters )
{
    BaseType_t err;
    while(1)
    {
        if(xHandleSemphrCounting != NULL)
        {
            err = xSemaphoreTake(xHandleSemphrCounting, portMAX_DELAY);
            if(err == pdTRUE)
            {
                printf("receive counting semphore...\r\n");
            }
        }
        vTaskDelay(1000);
    }
}

static void vTaskSemphrCountingGive( void* pvParameters )
{
    BaseType_t err;
    UBaseType_t current_count = 0;
    while(1)
    {
        if(xHandleSemphrCounting != NULL)
        {
            err = xSemaphoreGive(xHandleSemphrCounting);
            if(err == pdTRUE)
            {
                current_count = uxSemaphoreGetCount(xHandleSemphrCounting);
                printf("semphore get count = %d\r\n", (int)current_count);
            }
        }
        vTaskDelay(500);
    }
}

//priority invesion test
static void vTaskPriorityLow( void* pvParameters )
{
    while(1)
    {
        if(xHandleSemphrPrioInversion != NULL)
        {
            printf("vTaskPriorityLow request semaphore...\r\n");
            xSemaphoreTake(xHandleSemphrPrioInversion, portMAX_DELAY);
            printf("vTaskPriorityLow running...\r\n");
            for(uint32_t i = 0;i < 10000000; i++)
            {
                taskYIELD();
            }
            printf("vTaskPriorityLow give semaphore...\r\n");
            xSemaphoreGive(xHandleSemphrPrioInversion);
        }
        vTaskDelay(1000);
    }
}

static void vTaskPriorityMedium( void* pvParameters )
{
    while(1)
    {
        printf("vTaskPriorityMedium running...\r\n");
        vTaskDelay(1000);
    }
}

static void vTaskPriorityHigh( void* pvParameters )
{
    while(1)
    {
        if(xHandleSemphrPrioInversion != NULL)
        {
            printf("vTaskPriorityHigh request semaphore\r\n");
            xSemaphoreTake(xHandleSemphrPrioInversion, portMAX_DELAY);
            printf("vTaskPriorityHigh running...\r\n");
            printf("vTaskPriorityHigh give semaphore...\r\n");
            xSemaphoreGive(xHandleSemphrPrioInversion);
        }
        vTaskDelay(1000);
    }
}

//mutex semaphore test
static void vTaskMutexPriorityLow( void* pvParameters )
{
    while(1)
    {
        if(xHandleSemphrMutex != NULL)
        {
            printf("vTaskMutexPriorityLow request semaphore...\r\n");
            xSemaphoreTake(xHandleSemphrMutex, portMAX_DELAY);
            printf("vTaskMutexPriorityLow running...\r\n");
            for(uint32_t i = 0;i < 10000000; i++)
            {
                taskYIELD();
            }
            printf("vTaskMutexPriorityLow give semaphore...\r\n");
            xSemaphoreGive(xHandleSemphrMutex);
        }
        vTaskDelay(1000);
    }
}

static void vTaskMutexPriorityMedium( void* pvParameters )
{
    while(1)
    {
        printf("vTaskMutexPriorityMedium running...\r\n");
        vTaskDelay(1000);
    }
}

static void vTaskMutexPriorityHigh( void* pvParameters )
{
    while(1)
    {
        if(xHandleSemphrMutex != NULL)
        {
            printf("vTaskMutexPriorityHigh request semaphore\r\n");
            xSemaphoreTake(xHandleSemphrMutex, portMAX_DELAY);
            printf("vTaskMutexPriorityHigh running...\r\n");
            printf("vTaskMutexPriorityHigh give semaphore...\r\n");
            xSemaphoreGive(xHandleSemphrMutex);
        }
        vTaskDelay(1000);
    }
}