#include "app_task_create.h"
#include "global_include.h"

#define TASK_CREATE_LED_STK_SIZE    256
#define TASK_CREATE_PRINT_STK_SIZE  256
#define TASK_CREATE_DELETE_STK_SIZE 256

//优先级分配11-15
#define TASK_CREATE_LED_PRIO    11
#define TASK_CREATE_PRINT_PRIO  12
#define TASK_CREATE_DELETE_PRIO 13

TaskHandle_t xHandleTaskCreateLED = NULL;
TaskHandle_t xHandleTaskCreatePrint = NULL;
TaskHandle_t xHandleTaskCreateDelete = NULL;

static void vTaskCreateLED( void* pvParameters );
static void vTaskCreatePrint( void* pvParameters );
static void vTaskCreateDelete( void* pvParameters );


void vTaskCreateStart( void* pvParameters )
{
    printf("vTaskCreateStart running...\r\n");
    xTaskCreate( vTaskCreateLED,
                 "vTaskCreateLED",
                 TASK_CREATE_LED_STK_SIZE,
                 NULL,
                 TASK_CREATE_LED_PRIO,
                 &xHandleTaskCreateLED );

    xTaskCreate( vTaskCreatePrint,
                 "vTaskCreatePrint",
                 TASK_CREATE_PRINT_STK_SIZE,
                 NULL,
                 TASK_CREATE_PRINT_PRIO,
                 &xHandleTaskCreatePrint );

    xTaskCreate( vTaskCreateDelete,
                 "vTaskCreateDelete",
                 TASK_CREATE_DELETE_STK_SIZE,
                 NULL,
                 TASK_CREATE_DELETE_PRIO,
                 &xHandleTaskCreateDelete );
    vTaskDelete(NULL);
}

static void vTaskCreateLED( void* pvParameters )
{
    while(1)
    {
        printf("vTaskCreateLED running...\r\n");
        vTaskDelay(500);
    }
}

static void vTaskCreatePrint( void* pvParameters )
{
    float float_num = 0.00f;
    while(1)
    {
        float_num += 0.01f;
        printf("float_num = %.4f\r\n", float_num);
        vTaskDelay(1000);
    }
}

static void vTaskCreateDelete( void* pvParameters )
{
    uint8_t count = 0;
    while(1)
    {
        count++;
        printf("vTaskCreateDelete %d\r\n", count);
        if(count == 5)
        {
            vTaskDelete(xHandleTaskCreateLED);
        }
        else if(count == 10)
        {
            vTaskDelete(xHandleTaskCreatePrint);
        }
        else if(count == 15)
        {
            vTaskDelete(NULL);
        }
        vTaskDelay(1000);
    }

}


