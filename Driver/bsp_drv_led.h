#ifndef __BSP_DRV_LED_H
#define __BSP_DRV_LED_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx.h"


#define LED_NUM 5


#define LED_RED_L_PORT  GPIOA
#define LED_RED_L_PIN   GPIO_Pin_7
#define LED_GREEN_L_PORT GPIOA
#define LED_GREEN_L_PIN GPIO_Pin_6
#define LED_BLUE_L_PORT GPIOB
#define LED_BLUE_L_PIN  GPIO_Pin_12

#define LED_RED_R_PORT  GPIOC
#define LED_RED_R_PIN   GPIO_Pin_14
#define LED_GREEN_R_PORT    GPIOC
#define LED_GREEN_R_PIN GPIO_Pin_13


typedef enum 
{
	LED_BLUE_L = 0, 
	LED_GREEN_L, 
	LED_RED_L, 
	LED_GREEN_R, 
	LED_RED_R,
} led_e;

#define DATA_RX_LED		LED_GREEN_L	/*无线数据接收指示灯*/
#define DATA_TX_LED		LED_RED_L	/*无线数据发送指示灯*/
#define CHG_LED 		LED_BLUE_L	/*充电指示灯*/
#define LOWBAT_LED		LED_RED_R	/*电池低电量指示灯*/
#define SYS_LED   		LED_GREEN_R	/*系统心跳指示灯*/
#define ERR_LED1       	LED_RED_L	/*出错指示灯1*/
#define ERR_LED2       	LED_RED_R	/*出错指示灯2*/

void bsp_drv_led_init(void);
void bsp_drv_led_clear_all(void);
void bsp_drv_led_set_all(void);
void bsp_drv_led_on(led_e led);
void bsp_drv_led_off(led_e led);






#endif /* __BSP_DRV_LED_H */
