#ifndef __BSP_DRV_TIMER_H
#define __BSP_DRV_TIMER_H

#include "stm32f4xx.h"

extern volatile unsigned long long FreeRTOSRunTimeTicks;

void TIM3_Int_Init(u16 arr,u16 psc);
void ConfigureTimeForRunTimeStats(void);
void bsp_drv_timer9_init(uint16_t arr, uint16_t psc);



#endif /* __BSP_TIMER_H */
