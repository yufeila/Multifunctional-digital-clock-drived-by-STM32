#include "stm32f10x.h"                  // Device header
#include "DS1302.h"
#include "LCD1602.h"
//PB5  DS1302_CE
//PB6  DS1302_IO
//PB7  DS1302_CLK
//时间数组，索引0~6分别为年、月、日、时、分、秒、星期，设置为有符号的便于<0的判断
char DS1302_Time[]={24,8,28,13,56,55,2};

/**
  *  @brief  CE,SCLK端口初始化
  *  @param1	NONE
  *  @param2	NONE
  *  @return 	NONE
  */
void DS1302_GPIOInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //PB5  CE
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOC.5
	GPIO_ResetBits(GPIOB,GPIO_Pin_5); //初始化CE为0
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //PB7  SCLK
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.7
	GPIO_ResetBits(GPIOB,GPIO_Pin_7); //初始化SCLK为0
}

/**
  *  @brief  将IO口设置为输入模式并复位
  *  @param1	NONE
  *  @param2	NONE
  *  @return 	NONE
  */
void DS1302_IOOutputInit(void) //将IO口设置为输入模式并复位
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PB6  IO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOC.6
	GPIO_ResetBits(GPIOB,GPIO_Pin_6); //DATA_L
}

/**
  *  @brief  将IO口设置为输出模式并复位
  *  @param1	NONE
  *  @param2	NONE
  *  @return 	NONE
  */
void DS1302_IOInputInit(void)//
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PB6  IO
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOC.6
}

/**
  *  @brief  	向DS1302写入一个字节
  *  @param1	Command:命令字
  *  @param2	Data:写入数据
  *  @return 	NONE
  */
void DS1302_WriteByte(unsigned char Command,unsigned char Data)//向DS1302写入一个字节
{
	unsigned char i;
	CE_H;
	DS1302_IOOutputInit();//IO设置成输出模式
	
	for(i=0;i<8;i++)
	{
		if(Command&0x01){GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_SET);}
		else{GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_RESET);}
		SCLK_H;
		SCLK_L;
		Command=Command>>1;
	}
	
	for(i=0;i<8;i++)
	{
		if(Data&0x01){GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_SET);}
		else{GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_RESET);}
		SCLK_H;
		SCLK_L;
		Data=Data>>1;
	}
	
	CE_L;

}

/**
  *  @brief     从DS1302读出一个字节
  *  @param1	Command:指令字
  *  @param2	NONE
  *  @return 	读出字节
  */
unsigned char DS1302_ReadByte(unsigned char Command)//从DS1302读出一个字节
{
	unsigned char i,Data=0x00;
	Command|=0x01;//防止定义读指令码
	DS1302_IOOutputInit();
	CE_H;
	
	for(i=0;i<8;i++)
	{
		if(Command&0x01){GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_SET);}
		else{GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_RESET);}
		//先给0再给1，这样可以保证有15个脉冲。
		SCLK_L;
		SCLK_H;
		Command=Command>>1;
	}
	DS1302_IOInputInit();
	for(i=0;i<8;i++)
	{
		SCLK_H;
		SCLK_L; 
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)){Data=Data|(0x01<<i);}	
	}
	
	CE_L;
	DS1302_IOOutputInit();	//读取后将IO设置为0，否则读出的数据会出错
	return Data;
}

/**
  * @brief  DS1302设置时间，调用之后，DS1302_Time数组的数字会被设置到DS1302中
  * @param  无
  * @retval 无
  */
void DS1302_SetTime(void)
{
//	DS1302_WriteByte(DS1302_WP,0x00);//写入之前，关闭写保护
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);//十进制转BCD码后写入
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
//	DS1302_WriteByte(DS1302_WP,0x80);
	//如果写保护始终处于开启状态，会导致在运行时修改始终的值时无法写入，此时，需要关闭写保护。
}

/**
  * @brief  DS1302读取时间，调用之后，DS1302中的数据会被读取到DS1302_Time数组中
  * @param  无
  * @retval 无
  */
void DS1302_ReadTime(void)
{
	unsigned char Temp;
	Temp=DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0]=Temp/16*10+Temp%16;//BCD码转十进制后读取
	Temp=DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6]=Temp/16*10+Temp%16;
}

