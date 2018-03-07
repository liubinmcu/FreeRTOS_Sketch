#include "app_task_notification.h"
#include "global_include.h"
#include "limits.h"

#define TEST_NOTIFICATION_BINARY_SEMPHR     0
#define TEST_NOTIFICATION_COUNTING_SEMPHR   0
#define TEST_NOTIFICATION_MESSAGE_MAILBOX   0
#define TEST_NOTIFICATION_EVENT_GROUP       1

#define TASK_NOTIFICATION_GIVE_STK_SIZE 128
#define TASK_NOTIFICATION_TAKE_STK_SIZE 128


#define TASK_NOTIFICATION_GIVE_PRIO 15
#define TASK_NOTIFICATION_TAKE_PRIO 14


TaskHandle_t xHandleTaskNotificationGive = NULL;
TaskHandle_t xHandleTaskNotificationTake = NULL;

static void vTaskNotificationGive( void* pvParameters );
static void vTaskNotificationTake( void* pvParameters );


void vTaskNotificationStart( void* pvParameters )
{
    xTaskCreate( vTaskNotificationGive,
                 "vTaskNotificationGive",
                 TASK_NOTIFICATION_GIVE_STK_SIZE,
                 NULL,
                 TASK_NOTIFICATION_GIVE_PRIO,
                 &xHandleTaskNotificationGive );
    xTaskCreate( vTaskNotificationTake,
                 "vTaskNotificationTake",
                 TASK_NOTIFICATION_TAKE_STK_SIZE,
                 NULL,
                 TASK_NOTIFICATION_TAKE_PRIO,
                 &xHandleTaskNotificationTake );
    vTaskDelete(NULL);
}

static void vTaskNotificationGive( void* pvParameters )
{
    while(1)
    {
    #if (TEST_NOTIFICATION_BINARY_SEMPHR == 1 || TEST_NOTIFICATION_COUNTING_SEMPHR == 1)
        if(xHandleTaskNotificationTake != NULL)
            xTaskNotifyGive(xHandleTaskNotificationTake); 
    #endif
    #if (TEST_NOTIFICATION_MESSAGE_MAILBOX == 1)
        uint32_t Notification_Value = 0xAB;
        if(xHandleTaskNotificationTake != NULL)
        {
            xTaskNotify(xHandleTaskNotificationTake, Notification_Value, eSetValueWithOverwrite);
        }
    #endif
    #if (TEST_NOTIFICATION_EVENT_GROUP == 1)
        uint32_t Notification_Value = 0x80;
        if(xHandleTaskNotificationTake != NULL)
        {
            xTaskNotify(xHandleTaskNotificationTake, Notification_Value, eSetBits);
        }
    #endif
        printf("vTaskNotificationGive success!!!\r\n");
        vTaskDelay(200);
    }  
}

static void vTaskNotificationTake( void* pvParameters )
{
    uint32_t NotificationValue = 0;
    while(1)
    {
    #if (TEST_NOTIFICATION_BINARY_SEMPHR == 1)
        NotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("receive notification binary semphr value = %d\r\n", NotificationValue);
    #endif
    #if (TEST_NOTIFICATION_COUNTING_SEMPHR == 1)
        NotificationValue = ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
        printf("receive notification counting semphr value = %d\r\n", NotificationValue);
    #endif
    #if (TEST_NOTIFICATION_MESSAGE_MAILBOX == 1)
        BaseType_t err;
        err = xTaskNotifyWait(0, ULONG_MAX, &NotificationValue, portMAX_DELAY);
        if(err == pdPASS)
        {
            printf("receive notification message mailbox value = %#2x\r\n", NotificationValue);
        }
    #endif
    #if (TEST_NOTIFICATION_EVENT_GROUP == 1)
        BaseType_t err;
        err = xTaskNotifyWait(0, ULONG_MAX, &NotificationValue, portMAX_DELAY);
        if(err == pdPASS)
        {
            printf("receive notification event group value = %#2x\r\n", NotificationValue);
        }
    #endif
        vTaskDelay(1000);
    }
}



