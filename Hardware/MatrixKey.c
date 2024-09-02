#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MatrixKey_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
	
	//Row
	GPIO_InitTypeDef GPIO_InitStructure_H;
	GPIO_InitStructure_H.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure_H.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure_H.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure_H);						//将PA0~PA3引脚初始化为推挽输出
	
	//column
	GPIO_InitTypeDef GPIO_InitStructure_L;
	GPIO_InitStructure_L.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure_L.GPIO_Pin =GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_InitStructure_L.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure_L);						//将PA4~PA7引脚初始化为浮空输入
	
	GPIO_SetBits(GPIOA,GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3);
	//初始化为1111 1111
	
}

unsigned char MatrixKey_GetNum(void)
{
	unsigned char KeyNum=0;
	
	//first Line
	/*设置GPIO初始化后的默认电平*/
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0) //1110 1110
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0);
		Delay_ms(20);
		KeyNum = 1;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0) //1110 1101
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0);
		Delay_ms(20);
		KeyNum = 2;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0) 
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0);
		Delay_ms(20);
		KeyNum = 3;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0);
		Delay_ms(20);
		KeyNum = 4;
	}
	GPIO_SetBits(GPIOA,GPIO_Pin_0);

	
	//Second Line   
	GPIO_ResetBits(GPIOA,GPIO_Pin_1); //1111 1101
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0);
		Delay_ms(20);
		KeyNum = 5;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0);
		Delay_ms(20);
		KeyNum = 6;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0);
		Delay_ms(20);
		KeyNum = 7;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0);
		Delay_ms(20);
		KeyNum = 8;
	}
	GPIO_SetBits(GPIOA,GPIO_Pin_1); //1111 1101->1111 1111

	//Third Column      
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0);
		Delay_ms(20);
		KeyNum = 9;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0);
		Delay_ms(20);
		KeyNum = 10;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0);
		Delay_ms(20);
		KeyNum = 11;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0);
		Delay_ms(20);
		KeyNum = 12;
	}
	GPIO_SetBits(GPIOA,GPIO_Pin_2);//1111 1011->1111 1111
	
	//Forth Line
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0);
		Delay_ms(20);
		KeyNum = 13;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0);
		Delay_ms(20);
		KeyNum = 14;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0);
		Delay_ms(20);
		KeyNum = 15;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0);
		Delay_ms(20);
		KeyNum = 16;
	}
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	
	return KeyNum;
}	
