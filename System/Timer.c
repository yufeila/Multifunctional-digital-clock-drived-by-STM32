#include "stm32f10x.h"                  // Device header

int Minute,Second;
u8 Timer_Start,Timer_IT;

void Timer_Init(void)
{
	//开启TIM3外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//选择内部时钟源
	TIM_InternalClockConfig(TIM3);
	
	//初始化时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=10000-1;//定时1s
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;  //7200 0000/7200=10000HZ 0.1ms
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//手动将中断标志位清0，防止初始后立刻进入中断函数
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//打开更新中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置中断优先级
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
	
	/*暂时不使能时钟*/
//	TIM_Cmd(TIM3,ENABLE);
	
}

/*中断函数*/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		if(Timer_Start==1)
		{
			Second--;
		}
		
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}
	
