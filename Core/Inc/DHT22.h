#ifndef DHT22_H
#define DHT22_H

#include "stm32f1xx_hal.h"

#define DHT22_OK 0
#define DHT22_ERROR 1

void DHT22_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t DHT22_Read(float* temperature, float* humidity);


#endif
