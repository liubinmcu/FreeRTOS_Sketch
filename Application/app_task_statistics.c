#include "app_task_statistics.h"
#include "global_include.h"

#define TASK_STATISTIC_STK_SIZE    256
#define TASK_RUNTIME_STK_SIZE      256

#define TASK_STATISTIC_PRIO    11
#define TASK_RUNTIME_PRIO      12

TaskHandle_t xHandleTaskStatistic = NULL;
TaskHandle_t xHandleTaskRunTime = NULL;


char TaskStatusInfoBuffer[1000];
char TaskRunTimeInfoBuffer[1000];

static void vTaskStatusStatistic( void* pvParameters );
static void vTaskRunTimeStatistic( void* pvParameters );


void vTaskStatisticsStart( void* pvParameters )
{
    xTaskCreate( vTaskStatusStatistic,
                 "vTaskStatusStatistic",
                 TASK_STATISTIC_STK_SIZE,
                 NULL,
                 TASK_STATISTIC_PRIO,
                 &xHandleTaskStatistic );
    xTaskCreate( vTaskRunTimeStatistic,
                 "vTaskRunTimeStatistic",
                 TASK_RUNTIME_STK_SIZE,
                 NULL,
                 TASK_RUNTIME_PRIO,
                 &xHandleTaskRunTime );

    vTaskDelete(NULL);
}

static void vTaskStatusStatistic( void* pvParameters )
{
    vTaskList(TaskStatusInfoBuffer);
    printf("TaskName\t\t\tStatus\tPriority\tTaskNumber\t\t\r\n");
    printf("%s\r\n",TaskStatusInfoBuffer);
    while(1)
    {
        vTaskDelay(1000);
    }
}

static void vTaskRunTimeStatistic( void* pvParameters )
{
    vTaskGetRunTimeStats(TaskRunTimeInfoBuffer);
    printf("TaskName\t\t\tRunTime\t\tpercentage\r\n");
    printf("%s\r\n",TaskRunTimeInfoBuffer);
    while(1)
    {
        vTaskDelay(1000);
    }
}




