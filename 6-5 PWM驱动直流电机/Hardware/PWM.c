#include "stm32f10x.h" // Device header

void PWM_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 开启RCC内部时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM2); // 选择时基单元的时钟

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              // 配置时基单元
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 指定时钟分频率
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                 // ARR自动重装器的值
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;               // PSC预分频器的值
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            // 重复计数器的值
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             // 输出比较模式
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     // 输出比较极性
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 设置输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;                            // 设置CCR
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare3(uint16_t Compare)
{
    TIM_SetCompare3(TIM2, Compare);
}
