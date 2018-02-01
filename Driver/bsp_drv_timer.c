#include "bsp_drv_timer.h"
#include "global_include.h"

void bsp_drv_timer9_init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE); //ʹ��TIM9ʱ��
    
    TIM_TimeBaseInitStructure.TIM_Period = arr;         //�Զ���װ��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc;        //��ʱ����Ƶ
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStructure);  //��ʼ��TIM9
    
    TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);            //����ʱ��9�����ж�
    TIM_Cmd(TIM9,ENABLE);                               //ʹ�ܶ�ʱ��9
    
    NVIC_InitStructure.NVIC_IRQChannel=TIM1_BRK_TIM9_IRQn;      //��ʱ��9�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x08;  //��ռ���ȼ�8
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}


void TIM1_BRK_TIM9_IRQHandler(void)
{
    BaseType_t err = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint8_t receive_buffer[10] = {0};
	if(TIM_GetITStatus(TIM9,TIM_IT_Update)==SET) //����ж�
	{
        TIM_ClearITPendingBit(TIM9,TIM_IT_Update);  //����жϱ�־λ
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

