#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

void DQ_Init(void);
void DQ_Output(void);
void DQ_Input(void);
void DS18B20_Rst(void);
void DS18B20_Init(void);
uint8_t DS18B20_ReadByte(void);
void DS18B20_WriteByte(uint8_t data);
float DS18B20_GetTemp(void);


#endif