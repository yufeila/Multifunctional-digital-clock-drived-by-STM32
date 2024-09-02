#include "stm32f10x.h"                  // Device header
#include "Delay.h"                  // Device header
#include "LCD1602.h"
#include "MatrixKey.h"
#include "Stopwatch.h"
#include "DS1302.h"
#include "Buzzer.h"
#include "Timer.h"
#include "LED.h"
#include "DS18B20.h"

uint8_t KeyNum,MODE;
uint16_t num;
u8 TimeSetSelect;
u8 Flag_RTC,Flag_Stopwatch,Flag_Timer,Flag_Temperature;

u8 ACK;
float T;

void TimeShow(void)//时间显示功能
{
	DS1302_ReadTime();//读取时间

	LCD1602_ShowNum(0,0,DS1302_Time[0],2);//显示年
	LCD1602_ShowNum(0,3,DS1302_Time[1],2);//显示月
	LCD1602_ShowNum(0,6,DS1302_Time[2],2);//显示日
	LCD1602_ShowNum(1,0,DS1302_Time[3],2);//显示时
	LCD1602_ShowNum(1,3,DS1302_Time[4],2);//显示分
	LCD1602_ShowNum(1,6,DS1302_Time[5],2);//显示秒
}

void TimeSet(void)//时间设置功能
{
	if(KeyNum==6)//按键6按下
	{
		TimeSetSelect++;//设置选择位加1
		TimeSetSelect%=6;//越界清零
	}
	LCD1602_ShowNum(1,10,TimeSetSelect,2);

	if(KeyNum==10)//按键10按下
	{
		DS1302_Time[TimeSetSelect]++;//时间设置位数值加1
		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}//年越界判断
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}//月越界判断
		if( DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || 
			DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)//日越界判断
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}//大月
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}//小月
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}//闰年2月
			}
			else
			{
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}//平年2月
			}
		}
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}//时越界判断
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}//分越界判断
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}//秒越界判断
	}
	if(KeyNum==14)//按键14按下
	{
		DS1302_Time[TimeSetSelect]--;//时间设置位数值减1
		if(DS1302_Time[0]<0){DS1302_Time[0]=99;}//年越界判断
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}//月越界判断
		if( DS1302_Time[1]==1 || DS1302_Time[1]==3 || DS1302_Time[1]==5 || DS1302_Time[1]==7 || 
			DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)//日越界判断
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}//大月
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}//小月
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=29;}//闰年2月
				if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
			}
			else
			{
				if(DS1302_Time[2]<1){DS1302_Time[2]=28;}//平年2月
				if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
			}
		}
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}//时越界判断
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}//分越界判断
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}//秒越界判断
	}
	//更新显示，根据TimeSetSelect和TimeSetFlashFlag判断可完成闪烁功能
//	if(TimeSetSelect==0 && TimeSetFlashFlag==1){LCD_ShowString(1,1,"  ");}
//	else {LCD_ShowNum(1,1,DS1302_Time[0],2);}
//	if(TimeSetSelect==1 && TimeSetFlashFlag==1){LCD_ShowString(1,4,"  ");}
//	else {LCD_ShowNum(1,4,DS1302_Time[1],2);}
//	if(TimeSetSelect==2 && TimeSetFlashFlag==1){LCD_ShowString(1,7,"  ");}
//	else {LCD_ShowNum(1,7,DS1302_Time[2],2);}
//	if(TimeSetSelect==3 && TimeSetFlashFlag==1){LCD_ShowString(2,1,"  ");}
//	else {LCD_ShowNum(2,1,DS1302_Time[3],2);}
//	if(TimeSetSelect==4 && TimeSetFlashFlag==1){LCD_ShowString(2,4,"  ");}
//	else {LCD_ShowNum(2,4,DS1302_Time[4],2);}
//	if(TimeSetSelect==5 && TimeSetFlashFlag==1){LCD_ShowString(2,7,"  ");}
//	else {LCD_ShowNum(2,7,DS1302_Time[5],2);}
	LCD1602_ShowNum(0,0,DS1302_Time[0],2);//显示年
	LCD1602_ShowNum(0,3,DS1302_Time[1],2);//显示月
	LCD1602_ShowNum(0,6,DS1302_Time[2],2);//显示日
	LCD1602_ShowNum(1,0,DS1302_Time[3],2);//显示时
	LCD1602_ShowNum(1,3,DS1302_Time[4],2);//显示分
	LCD1602_ShowNum(1,6,DS1302_Time[5],2);//显示秒
}


int main(void)
{
	LCD1602_Init();
	MatrixKey_Init();
	DS1302_GPIOInit();
	DS1302_SetTime();
	Stopwatch_Init();
	Timer_Init();
	Buzzer_Init();
	DS18B20_Init();
	
	
	while(1)
	{
		KeyNum=MatrixKey_GetNum();
		//Clock——DS1302
		if(KeyNum==2)//按键2按下
		{
			Flag_RTC=1;
			Flag_Stopwatch=0;
			LCD1602_Clear();
			LCD1602_ShowStr(0,0,(u8*)"  -  -  ");//静态字符初始化显示
			LCD1602_ShowStr(1,0,(u8*)"  :  :  ");
			if(MODE==0){MODE=1;}//功能切换
			else if(MODE==1){MODE=0;Delay_us(10);DS1302_SetTime();}
			LCD1602_ShowNum(0,10,MODE,1);
		}
		switch(MODE)//根据不同的功能执行不同的函数
		{
			case 0:if(Flag_RTC)TimeShow();break;
			case 1:if(Flag_RTC)TimeSet();break;
		}
		
		
		//Stopwatch
		if(KeyNum==1)
		{
			//Initialize
			if(Flag_Stopwatch==0)
			{
				Flag_Stopwatch=1;
				Flag_RTC=0;
				LCD1602_Clear();
				LCD1602_ShowStr(0,0,(u8*)"  :  .  ");//静态字符初始化显示
				TIM_Cmd(TIM2,ENABLE); //使能TIM2
			}
			else if(Flag_Stopwatch==1)
			{
				Flag_Stopwatch=0;
				TIM_Cmd(TIM2,DISABLE);//失能TIM2
				LCD1602_Clear();
			}
		}
//		LCD1602_ShowNum(0,11,KeyNum,2);
//		LCD1602_ShowNum(1,11,Flag_Stopwatch,2);
		if(Flag_Stopwatch==1)
		{
			LCD1602_ShowNum(0,0,min,2);
			LCD1602_ShowNum(0,3,s,2);
			LCD1602_ShowNum(0,6,ms,2);
			if(KeyNum==5)
			{
				//开始走时
				Stopwatch_Start=1;
				Stopwatch_Stop=0;
				Stopwatch_Clear=0;
			}
			if(KeyNum==9)
			{
				//暂停
				if(Stopwatch_Start==1) //在走时状态下才能暂停；
				{
					Stopwatch_Stop=1;
					Stopwatch_Clear=0;
				}
			}
			if(KeyNum==13)
			{
				//计时清0 
				Stopwatch_Clear=1;
				Stopwatch_Start=0;
				Stopwatch_Stop=0;
			}
		}

		//Timer
//		LCD1602_ShowNum(0,11,Timer_IT,2);
//		LCD1602_ShowNum(1,11,Flag_Timer,2);
		if(KeyNum==3)
		{
			if(Flag_Timer==0)
			{	
				Flag_Timer=1; //定时器开启
				Flag_Stopwatch=0;
				Flag_RTC=0;
				LCD1602_Clear();
				LCD1602_ShowStr(0,0,(u8*)"  :  ");
				TIM_Cmd(TIM3,ENABLE);
			}
			else if(Flag_Timer==1)
			{
				Flag_Timer=0;//定时器关闭
				TIM_Cmd(TIM3,DISABLE);
				
			}
			
		}
		if(Flag_Timer==1)
		{

			//设置时间(min)
			if(KeyNum==7)
			{
				Minute++;
			}
			//设置时间(s)
			if(KeyNum==11)
			{
				Second++;
				if(Second>=60)
				{
					Minute++;
					Second=0;
				}
			}
			//倒计时启动
			if(KeyNum==15)
			{
				Timer_Start=1;
			}
			if(Timer_Start==1)
			{
				if(Second<0)
				{
					Second=59;
					Minute--;
				}
				if(Minute==0&&Second==0)
				{
					Timer_IT=1;
					Timer_Start=0;
				}
			}
			
			LCD1602_ShowNum(0,0,Minute,2);
			LCD1602_ShowNum(0,3,Second,2);
			if(Timer_IT==1)
			{
				LED1_ON();
				Delay_ms(500);
				LED1_OFF();
				Delay_ms(500);
				LED1_ON();
				Delay_ms(500);
				LED1_OFF();
				Delay_ms(500);
				LED1_ON();
				Delay_ms(500);
				LED1_OFF();
				
				Timer_IT=0;
			}
			
		}
		if(KeyNum==4)
		{
			if(Flag_Temperature==0)
			{
				Flag_Temperature=1;
			}
			else if(Flag_Temperature==1)
			{
				Flag_Temperature=0;
				LCD1602_Clear();
			}
			
		}

		if(Flag_Temperature==1)
		{
			LCD1602_ShowStr(0,0,(u8*)"Temperature:");
			T=DS18B20_GetTemp();
			if(T<0)
			{
				LCD1602_ShowChar(1,0,'-');
				T=-T;
			}
			else
			{
				LCD1602_ShowChar(1,0,'+');
			}
			LCD1602_ShowNum(1,1,T,3);
			LCD1602_ShowChar(1,4,'.');
			LCD1602_ShowNum(1,5,(unsigned long)(T*10000)%10000,3);
				
		}
		
	}
}
