#include "stm32f10x.h"                  // Device header
#include "Delay.h"
//PA12  DQ
//#define OneWire_DQ_HIGH 	GPIO_SetBits(GPIOA,GPIO_Pin_12)
//#define OneWire_DQ_LOW 		GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#define ONE_WIRE_DQ_HIGH   GPIO_SetBits(GPIOA, GPIO_Pin_12)
#define ONE_WIRE_DQ_LOW    GPIO_ResetBits(GPIOA, GPIO_Pin_12)


#define DS18B20_SKIP_ROM 			0xCC
#define DS18B20_CONVERT_T 			0x44
#define DS18B20_READ_SCRATCHPAD 	0xBE


//void DQ_Init(void)
//{
//	/*开启时钟*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
//	
//	/*GPIO初始化*/
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
//	
//}


//void DQ_Output(void)
//{
//	/*开启时钟*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
//	
//	/*GPIO初始化*/
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
//	
//	/*设置GPIO初始化后的默认电平*/
//	GPIO_SetBits(GPIOA,GPIO_Pin_12);	
//}

//void DQ_Input(void)
//{
//	/*开启时钟*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
//	
//	/*GPIO初始化*/
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //设置为输入模式
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
//	
//}

//void DS18B20_Rst(void)
//{
//	DQ_Output();
//	OneWire_DQ_HIGH;
//	Delay_us(1);
//	OneWire_DQ_LOW;
//	Delay_us(750); //Delay 500us
//	OneWire_DQ_HIGH;
//	Delay_us(500);//Delay 70us
//	DQ_Input();
//	uint8_t dqStatus=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
//	OneWire_DQ_HIGH;
//	
//}

//void DS18B20_Init(void)
//{
//	DQ_Input();
//	DS18B20_Rst();
//}

//uint8_t DS18B20_ReadByte(void)
//{
//	uint8_t data = 0x00;
//	for(int i=0;i<8;i++)
//	{
//		DQ_Output();
//		/*将数据线拉高*/
//		OneWire_DQ_HIGH;
//		/*延时2us*/
//		Delay_us(2);
//		/*将数据线拉低*/
//		OneWire_DQ_LOW;
//		/*延时3us*/
//		Delay_us(3);
//		data>>=1;
//		/*将数据线拉高*/
//		OneWire_DQ_HIGH;
//		DQ_Input();
//		/*延时5us*/
//		Delay_us(5);
//		/*读数据线得到一个状态位，并进行数据处理*/
//		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12))
//		{
//			data|=0x80;
//		}	
//		Delay_us(60);
//		
//	}
//	return data;
//}

//void DS18B20_WriteByte(uint8_t data)
//{
//	for(int i=0;i<8;i++)
//	{
//		OneWire_DQ_LOW;
//		Delay_us(15);
//		if(data&0x01)
//		{
//			GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET);
//			
//		}
//		else
//		{
//			GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_RESET);

//		}
//		Delay_us(45);
//		OneWire_DQ_HIGH;
//		data>>=1;
//	}
//}

//float DS18B20_GetTemp(void)
//{
//	DS18B20_Rst();
//	DS18B20_WriteByte(DS18B20_SKIP_ROM);
//	DS18B20_WriteByte(DS18B20_CONVERT_T);
//	Delay_us(750);
//	DS18B20_Rst();
//	DS18B20_WriteByte(DS18B20_SKIP_ROM);
//	DS18B20_WriteByte(DS18B20_CONVERT_T);
//	Delay_us(750);
//	uint8_t tempL=DS18B20_ReadByte();
//	uint8_t tempH=DS18B20_ReadByte();

//	if(tempH>0x7f) //0111 1111 
//	{
//		tempL=~tempL;
//		tempH=~tempH+1;
//	}
//	
//	float temp=((tempH<<4)|(tempL>>4))+(float)(tempL&0x0f)*0.0625;
//	
//	return temp;
//}

void DQ_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DQ_Output(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DQ_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DS18B20_Rst(void)
{
    DQ_Output();
    ONE_WIRE_DQ_LOW;
    Delay_us(480); // Minimum 480us reset pulse
    ONE_WIRE_DQ_HIGH;
    Delay_us(70);  // Wait for the presence pulse
    DQ_Input();
    Delay_us(410); // Wait for presence detection
}

void DS18B20_Init(void)
{
    DQ_Init();
    DS18B20_Rst();
}

uint8_t DS18B20_ReadByte(void)
{
    uint8_t data = 0;
    for (int i = 0; i < 8; i++)
    {
        DQ_Output();
        ONE_WIRE_DQ_LOW;
        Delay_us(1);
        ONE_WIRE_DQ_HIGH;
        DQ_Input();
        Delay_us(14);
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12))
        {
            data |= (1 << i);
        }
        Delay_us(45);
    }
    return data;
}

void DS18B20_WriteByte(uint8_t data)
{
    for (int i = 0; i < 8; i++)
    {
        DQ_Output();
        ONE_WIRE_DQ_LOW;
        Delay_us(1);
        if (data & (1 << i))
        {
            ONE_WIRE_DQ_HIGH;
        }
        Delay_us(60);
        ONE_WIRE_DQ_HIGH;
        Delay_us(5);
    }
}

float DS18B20_GetTemp(void)
{
    DS18B20_Rst();
    DS18B20_WriteByte(DS18B20_SKIP_ROM);
    DS18B20_WriteByte(DS18B20_CONVERT_T);
    Delay_ms(750); // Wait for temperature conversion
    DS18B20_Rst();
    DS18B20_WriteByte(DS18B20_SKIP_ROM);
    DS18B20_WriteByte(DS18B20_READ_SCRATCHPAD);
    uint8_t tempL = DS18B20_ReadByte();
    uint8_t tempH = DS18B20_ReadByte();

    int16_t temp = (tempH << 8) | tempL;
    float temperature = temp * 0.0625;

    return temperature;
}