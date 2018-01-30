#ifndef __BSP_DRV_MOTORS_H
#define __BSP_DRV_MOTORS_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"

/* 96M��Ƶ�� 8λ�������375K PWM */
#define TIM_CLOCK_HZ 				96000000
#define MOTORS_PWM_BITS           	8
#define MOTORS_PWM_PERIOD         	((1<<MOTORS_PWM_BITS) - 1)
#define MOTORS_PWM_PRESCALE       	0

//#define ENABLE_THRUST_BAT_COMPENSATED	/*ʹ�ܵ�����Ų���*/

#define NBR_OF_MOTORS 	4
#define MOTOR_M1  		0
#define MOTOR_M2  		1
#define MOTOR_M3  		2
#define MOTOR_M4  		3

#define MOTORS_TEST_RATIO         (u16)(0.2*(1<<16))	//20%
#define MOTORS_TEST_ON_TIME_MS    50
#define MOTORS_TEST_DELAY_TIME_MS 150

void bsp_drv_motors_init(void);
void bsp_drv_motors_set_ratio(u32 id, u16 ithrust);


#endif /* __BSP_DRV_MOTORS_H */