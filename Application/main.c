#include "bsp_hardware.h"
#include "app_task_main.h"
#include "global_include.h"


void main( void )
{
    printf( "FreeRTOS_Sketch Start......\r\n" );
    bsp_hardware_init();
    /* �������� */
    app_task_create();
    /* �������ȣ���ʼִ������ */
    vTaskStartScheduler();
    while( 1 )
    {
      
    }
}

