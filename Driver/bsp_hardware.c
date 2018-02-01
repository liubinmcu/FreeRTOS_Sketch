#include "bsp_hardware.h"
#include "bsp_drv_led.h"
#include "bsp_drv_motors.h"
#include "bsp_drv_timer.h"
#include "global_include.h"


void bsp_hardware_init(void)
{
    /* Setup STM32 system (clock, PLL and Flash configuration) */
    SystemInit();

    /* Ensure all priority bits are assigned as preemption priority bits. */
    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

//    delay_init(168);     /*delay≥ı ºªØ*/
//    bsp_drv_led_init();
//    bsp_drv_motors_init();
//    bsp_drv_timer9_init(5000, 16800-1);

}
