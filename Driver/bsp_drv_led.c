#include "bsp_drv_led.h"
//#include "delay.h"


/*LED 极性*/
#define LED_POL_POS 0
#define LED_POL_NEG 1

static bool isInit = false;

typedef struct
{
    GPIO_TypeDef* port;
    u16 pin;
    int polarity;
} led_t;

static led_t leds[LED_NUM] =
{
    [LED_BLUE_L]    = {LED_BLUE_L_PORT, LED_BLUE_L_PIN, LED_POL_POS},
    [LED_GREEN_L]   = {LED_GREEN_L_PORT, LED_GREEN_L_PIN,  LED_POL_NEG},
    [LED_RED_L]     = {LED_RED_L_PORT, LED_RED_L_PIN,  LED_POL_NEG},
    [LED_GREEN_R]   = {LED_GREEN_R_PORT, LED_GREEN_R_PIN, LED_POL_NEG},
    [LED_RED_R]     = {LED_RED_R_PORT, LED_RED_R_PIN, LED_POL_NEG},
};

/* LED测试 */
static bool led_test(void)
{
	bsp_drv_led_on(LED_GREEN_L);
	bsp_drv_led_on(LED_GREEN_R);
	bsp_drv_led_off(LED_RED_L);
	bsp_drv_led_off(LED_RED_R);
//	delay_xms(250);
	
	bsp_drv_led_off(LED_GREEN_L);
	bsp_drv_led_off(LED_GREEN_R);
	bsp_drv_led_on(LED_RED_L);
	bsp_drv_led_on(LED_RED_R);

//	delay_xms(250);

	bsp_drv_led_clear_all();
	bsp_drv_led_on(LED_BLUE_L);

	return isInit;
}


/* LED初始化 */
void bsp_drv_led_init( void )
{
    if( isInit )
    {
        return;
    }
    GPIO_InitTypeDef GPIO_InitStructure;
    /*使能led时钟*/
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
    /*LED_GREEN_L PA6   LED_RED_L PA7*/
    GPIO_InitStructure.GPIO_Pin = LED_GREEN_L_PIN | LED_RED_L_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init( LED_GREEN_L_PORT, &GPIO_InitStructure );
    /*LED_BLUE_L PB12*/
    GPIO_InitStructure.GPIO_Pin = LED_BLUE_L_PIN;
    GPIO_Init( LED_BLUE_L_PORT, &GPIO_InitStructure );
    /*LED_GREEN_R PC13  LED_RED_R PC14*/
    GPIO_InitStructure.GPIO_Pin = LED_GREEN_R_PIN | LED_RED_R_PIN;
    GPIO_Init( LED_GREEN_R_PORT, &GPIO_InitStructure );
    bsp_drv_led_clear_all();
    isInit = true;
//    while (isInit)
//    {
//        led_test();
//    }
}

/*关闭所有LED*/
void bsp_drv_led_clear_all( void )
{
    for( u8 i = 0; i < LED_NUM; i++ )
    {
        bsp_drv_led_off( ( led_e )i );
    }
}

/*打开所有LED*/
void bsp_drv_led_set_all( void )
{
    for( u8 i = 0; i < LED_NUM; i++ )
    {
        bsp_drv_led_on( ( led_e )i );
    }
}


void bsp_drv_led_on( led_e led )
{
    uint8_t value = 1;
    if( led > LED_NUM )
    {
        return;
    }
    if( leds[led].polarity == LED_POL_NEG )
    {
        value = !value;
    }
    if( value )
    {
        GPIO_SetBits( leds[led].port, leds[led].pin );
    }
    else
    {
        GPIO_ResetBits( leds[led].port, leds[led].pin );
    }
}

void bsp_drv_led_off( led_e led )
{
    uint8_t value = 0;
    if( led > LED_NUM )
    {
        return;
    }
    if( leds[led].polarity == LED_POL_NEG )
    {
        value = !value;
    }
    if( value )
    {
        GPIO_SetBits( leds[led].port, leds[led].pin );
    }
    else
    {
        GPIO_ResetBits( leds[led].port, leds[led].pin );
    }
}



