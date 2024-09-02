#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "stm32f10x.h"                  // Device header


/* 端口操作宏定义*/
#define  RS_H   GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define  RS_L   GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define  RW_H   GPIO_SetBits(GPIOB,GPIO_Pin_2)
#define  RW_L   GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define  EN_H   GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define  EN_L   GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define  READ_BUSY()   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) //最高位

/*通过直接配置寄存器来改变PB15是输入还是输出*/
#define  PB15_OUT()  {GPIOB->CRH&=0xFFFFFFF;GPIOB->CRH|=0x30000000;}
#define  PB15_IN()  {GPIOB->CRH&=0xFFFFFFF;GPIOB->CRH|=0x80000000;}

/*驱动函数声明*/
_Bool LCD1602_WaitReady(void); //等待液晶就绪，（读忙函数）
void LCD1602_SendByte(u8 byte); //向液晶写入一个字节
void LCD1602_WriteCmd(u8 byte); //向LCD11602写命令;
void LCD1602_WriteData(u8 byte);//向LCD1602写数据;
void LCD1602_SetCursor(u8 x,u8 y);//设置显示RAM的地址，及光标位置;
void LCD1602_ShowChar(u8 x,u8 y,char ch);//在液晶屏上显示单个字符
void LCD1602_ShowStr(u8 x,u8 y,u8* str);//显示字符串;
void LCD1602_Init(void);//LCD初始化
int LCD1602_Pow(int X,int Y);
void LCD1602_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD1602_Clear(void);	

#endif