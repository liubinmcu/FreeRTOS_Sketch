#include "bsp_hardware.h"
#include "app_task_main.h"
#include "global_include.h"


void main( void )
{
    printf( "FreeRTOS_Sketch Start......\r\n" );
    bsp_hardware_init();
    /* 创建任务 */
    app_task_create();
    /* 启动调度，开始执行任务 */
    vTaskStartScheduler();
    while( 1 )
    {
      
    }
}

