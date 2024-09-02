#include "LCD1602.h"                  // Device header
#include "Delay.h"




///**
//  *  @brief    等待液晶准备好
//  *  @param1   无
//  *  @param2	 无
//  *  @return   1：忙;0:不忙
//  */
//_Bool LCD1602_WaitReady(void)
//{
//	PB15_IN();  //0准备：PB15设称输入
//	RS_L;		//1拉低RS:命令模式
//	RW_H;       //2拉高RW:读模式
//	EN_L;       
//	Delay_us(1); //产生使能的高脉冲
//	EN_H;
//	return (_Bool)READ_BUSY(); //4返回读到PB15的数据
//	
//}

/**
  *  @brief  向LCD1602写入一个字节
  *  @param1	byte:需要写入的数据
  *  @param2  无
  *  @return  无
  */
void LCD1602_SendByte(u8 byte)
{
	u16 value = 0;
	value = GPIO_ReadOutputData(GPIOB); //读取GPIOB的数据
	value &=0xFF; //0000 0000 1111 1111 &xxxx xxxx xxxx xxxx=0000 0000 xxxx xxxx
	value |=(u16)byte << 8 ;//0000 0000 yyyy yyyy << 8=yyyy yyyy 0000 0000->yyyy yyyy xxxx xxxx
	GPIO_Write(GPIOB,value);
	
	Delay_us(10);
}

/**
  *  @brief   向LCD11602写命令
  *  @param1	byte:需要写入的命令
  *  @param2
  *  @return 无
  */
void LCD1602_WriteCmd(u8 byte)
{

	RS_L;//拉低RS:命令模式
	RW_L;//拉低RW:写操作	
	LCD1602_SendByte(byte);//发送一个命令字节
	EN_H;
	Delay_ms(1);
	EN_L; //拉低使能释放总线
	Delay_ms(1);
}

/**
  *  @brief     向LCD1602写数据
  *  @param1    byte:需要写入的数据
  *  @param2	  无
  *  @return    无
  */

void LCD1602_WriteData(u8 byte)
{

	RS_H;
	RW_L;
	LCD1602_SendByte(byte);
	EN_H;
	Delay_ms(1);
	EN_L;
	Delay_ms(1);
	
}

/**
  *  @brief  设置显示RAM的地址，及光标位置
  *  @param1  x:行坐标(0是第一行，1是第二行)
  *  @param2  y:列坐标(0~15)
  *  @return 无
  */
void LCD1602_SetCursor(u8 x,u8 y)
{
	u8 addr;
	//由输入的屏幕坐标计算RAM的地址
	if(x==0)
		addr = 0x00 + y;
	else
		addr = 0x40 + y;
	LCD1602_WriteCmd(addr|0x80);//指令码最高位为1，剩下七位为RAM地址
}

/**
  *  @brief  在液晶屏上显示单个字符
  *  @param1 x:横坐标；y：纵坐标
  *  @param2 ch:待显示的字符
  *  @return 无
  */
void LCD1602_ShowChar(u8 x,u8 y,char ch)
{
	LCD1602_SetCursor(x,y);
	LCD1602_WriteData(ch);
}

/**
  *  @brief  显示字符串
  *  @param1 x,y
  *  @param2 字符串指针
  *  @return 无
  */
void LCD1602_ShowStr(u8 x,u8 y,u8* str)
{
	LCD1602_SetCursor(x,y);
	while(*str)
	{
		LCD1602_WriteData(*str);
		str++;
	}
}

/**
  * @brief  返回值=X的Y次方
  */
int LCD1602_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

/**
  * @brief  在LCD1602指定位置开始显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~65535
  * @param  Length 要显示数字的长度，范围：1~5
  * @retval 无
  */
void LCD1602_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD1602_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD1602_WriteData(Number/LCD1602_Pow(10,i-1)%10+'0');
	}
}


/**
  *  @brief  LCD1602初始化
  *  @param1 无
  *  @param2 无   
  *  @return 无
  */
/*说明：RW = PB2 ; RS = PB1 ; EN = PB0
		D0~D7 = PB8~PB15;
*/
void LCD1602_Init(void)
{
	//定义GPIO初始化结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//开启GPIOB外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//根据手册的初始化流程编写
	LCD1602_WriteCmd(0x38);
	LCD1602_WriteCmd(0x0C);
	LCD1602_WriteCmd(0x06);
	LCD1602_WriteCmd(0x01);
	
	Delay_us(200);
	
}
/**
  *  @brief  清屏，光标回到初始位置
  *  @param1	NONE
  *  @param2	NONE
  *  @return 	NONE
  */
void LCD1602_Clear(void)
{
	LCD1602_WriteCmd(0x01);
}