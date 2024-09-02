#include "stm32f10x.h"                  // Device header

extern uint16_t num;
u8 min,s,ms;//分钟，秒，毫秒
u8 Stopwatch_Start,Stopwatch_Stop,Stopwatch_Clear;

void Stopwatch_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//定时1秒
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;  //7200 0000/7200=10000HZ 0.1ms
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//手动将中断标志位清0，防止初始后立刻进入中断函数
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
//	TIM_Cmd(TIM2,ENABLE);
	

}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		if(Stopwatch_Start==1)
		{
			if(Stopwatch_Stop==1)
			{
			
			}
			else
			{
				ms++;
				if(ms>=100)
				{
					s++;
					ms=0;
				}
				if(s>=60)
				{
					min++;
					s=0;
				}
			}
			
			
			
		}
		if(Stopwatch_Clear==1)
		{
			min=0;
			s=0;
			ms=0;
			Stopwatch_Clear=0;
		}
		
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}


