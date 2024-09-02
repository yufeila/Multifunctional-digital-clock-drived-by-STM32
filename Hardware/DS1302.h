#ifndef __DS1302_H__
#define __DS1302_H__
//PB5  DS1302_CE
//PB6  DS1302_IO
//PB7  DS1302_CLK
//寄存器写入地址/指令定义
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E

#define CE_L GPIO_ResetBits(GPIOB,GPIO_Pin_5)//拉低使能位
#define CE_H GPIO_SetBits(GPIOB,GPIO_Pin_5)//拉高使能位
#define SCLK_L GPIO_ResetBits(GPIOB,GPIO_Pin_7)//拉低时钟线
#define SCLK_H  GPIO_SetBits(GPIOB,GPIO_Pin_7)//拉高时钟线
#define DATA_L  GPIO_ResetBits(GPIOB,GPIO_Pin_6)//拉低数据线
#define DATA_H  GPIO_SetBits(GPIOB,GPIO_Pin_6)//拉高数据线

//外部可调用时间数组，索引0~6分别为年、月、日、时、分、秒、星期，设置为有符号的便于<0的判断
extern char DS1302_Time[];

void DS1302_GPIOInit();//CE,SCLK端口初始化
void DS1302_IOOutputInit(void);//将IO口设置为输出模式并复位
void DS1302_IOInputInit(void);//将IO口设置为输入模式并复位
void DS1302_WriteByte(unsigned char Command,unsigned char Data);//向DS1302写入一个字节
unsigned char DS1302_ReadByte(unsigned char Command);//从DS1302读出一个字节
void DS1302_SetTime(void);//DS1302设置时间，调用之后，DS1302_Time数组的数字会被设置到DS1302中
void DS1302_ReadTime(void);//DS1302读取时间，调用之后，DS1302中的数据会被读取到DS1302_Time数组中




#endif