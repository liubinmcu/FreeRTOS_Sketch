#include "bsp_hardware.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#define TASK_START_STK_SIZE 128
#define TASK_LED_STK_SIZE   512
#define TASK_PRINT_STK_SIZE 512
#define TASK_MSG_STK_SIZE   512


#define TASK_START_PRIO 1
#define TASK_LED_PRIO   2
#define TASK_PRINT_PRIO 3
#define TASK_MSG_PRIO   4


static void AppTaskCreate( void );
static void vTaskStart( void* pvParameters );
static void vTaskLED( void* pvParameters );
static void vTaskPrint( void* pvParameters );
static void vTaskMsg( void* pvParameters );


/*
**********************************************************************************************************
                                            ��������
**********************************************************************************************************
*/
TaskHandle_t xHandleTaskStart = NULL;
TaskHandle_t xHandleTaskLED = NULL;
TaskHandle_t xHandleTaskPrint = NULL;
TaskHandle_t xHandleTaskMsg = NULL;

void main( void )
{
    printf( "Template_FreeRTOS Start......\r\n" );
    /* �������� */
    AppTaskCreate();
    /* �������ȣ���ʼִ������ */
    vTaskStartScheduler();
    while( 1 )
    {
      
    }
}

static void AppTaskCreate(void)
{
    xTaskCreate( vTaskStart,       /* ������  */
                 "vTaskStart",         /* ������    */
                 TASK_START_STK_SIZE,                   /* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,                  /* �������  */
                 TASK_START_PRIO,                     /* �������ȼ�*/
                 &xHandleTaskStart );  /* ������  */
}

static void vTaskStart( void* pvParameters )
{
    xTaskCreate( vTaskLED,       /* ������  */
                 "vTaskLED",         /* ������    */
                 TASK_LED_STK_SIZE,                   /* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,                  /* �������  */
                 TASK_LED_PRIO,                     /* �������ȼ�*/
                 & xHandleTaskLED);  /* ������  */
    xTaskCreate( vTaskPrint,          /* ������  */
                 "vTaskPrint",        /* ������    */
                 TASK_PRINT_STK_SIZE,               /* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,              /* �������  */
                 TASK_PRINT_PRIO,                 /* �������ȼ�*/
                 &xHandleTaskPrint ); /* ������  */
    xTaskCreate( vTaskMsg,          /* ������  */
             "vTaskMsg",        /* ������    */
             TASK_MSG_STK_SIZE,               /* ����ջ��С����λword��Ҳ����4�ֽ� */
             NULL,              /* �������  */
             TASK_MSG_PRIO,                 /* �������ȼ�*/
             &xHandleTaskMsg ); /* ������  */
    vTaskDelete(xHandleTaskStart);
}

static void vTaskLED( void* pvParameters )
{
    static uint8_t count = 0;
    while( 1 )
    {
        count++;
        printf( "vTaskLED start %d\r\n", count);
        if(count == 5)
        {
            vTaskDelete(xHandleTaskPrint);
        }
        else if(count == 10)
        {
            vTaskDelete(xHandleTaskMsg);
        }
        else if(count == 15)
        {
            vTaskDelete(xHandleTaskLED);
        }
        vTaskDelay( 1000 );
    }
}

static void vTaskPrint( void* pvParameters )
{
    static float float_num = 0.00;
    while( 1 )
    {
        float_num += 0.01f;
        printf( "float_num��ֵΪ: %.4f\r\n", float_num );
        vTaskDelay( 100 );
    }
}

static void vTaskMsg( void* pvParameters )
{
    while( 1 )
    {
        printf( "vTaskMsg start\r\n");
        vTaskDelay( 500 );
    }
}



