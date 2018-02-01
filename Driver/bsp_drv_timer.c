#include "bsp_drv_timer.h"
#include "global_include.h"

void bsp_drv_timer9_init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE); //使能TIM9时钟
    
    TIM_TimeBaseInitStructure.TIM_Period = arr;         //自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc;        //定时器分频
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStructure);  //初始化TIM9
    
    TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);            //允许定时器9更新中断
    TIM_Cmd(TIM9,ENABLE);                               //使能定时器9
    
    NVIC_InitStructure.NVIC_IRQChannel=TIM1_BRK_TIM9_IRQn;      //定时器9中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x08;  //抢占优先级8
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}


void TIM1_BRK_TIM9_IRQHandler(void)
{
    BaseType_t err = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint8_t receive_buffer[10] = {0};
	if(TIM_GetITStatus(TIM9,TIM_IT_Update)==SET) //溢出中断
	{
        TIM_ClearITPendingBit(TIM9,TIM_IT_Update);  //清除中断标志位
        if(xHandleQueueMsg != NULL)
        {
            err = xQueueReceiveFromISR(xHandleQueueMsg, receive_buffer, &xHigherPriorityTaskWoken);
            if(err == pdTRUE)
            {
                printf("receive data from IRQ: %s\r\n", receive_buffer);
            }
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
	}
	

}

