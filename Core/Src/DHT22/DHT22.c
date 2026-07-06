#include "DHT22.h"
#include "main.h"

static GPIO_TypeDef* DHT22_PORT;
static uint16_t DHT22_PIN;

void DHT22_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    DHT22_PORT = GPIOx;
    DHT22_PIN = GPIO_Pin;
}

static void DHT22_SetPinOutput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT22_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT22_PORT, &GPIO_InitStruct);
}

static void DHT22_SetPinInput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT22_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT22_PORT, &GPIO_InitStruct);
}

static uint8_t DHT22_CheckResponse(void)
{
    uint8_t response = 0;
    DHT22_SetPinInput();
    HAL_Delay(1);

    if (!HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN))
    {
        HAL_Delay(1);
        if (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN))
            response = 1;
    }

    while (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)); // wait till pin goes low
    return response;
}

static uint8_t DHT22_ReadByte(void)
{
    uint8_t i, byte = 0;
    for (i = 0; i < 8; i++)
    {
        while (!HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)); // wait for high
        HAL_Delay(0.04); // 40us delay

        if (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN))
            byte = (byte << 1) | 1;
        else
            byte = (byte << 1);

        while (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)); // wait for low
    }
    return byte;
}

uint8_t DHT22_Read(float* temperature, float* humidity)
{
    uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2, sum;
    uint16_t RH, TEMP;

    DHT22_SetPinOutput();
    HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, GPIO_PIN_RESET);
    HAL_Delay(1); // at least 1ms
    HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, GPIO_PIN_SET);
    HAL_Delay(0.03); // 30us

    if (DHT22_CheckResponse())
    {
        Rh_byte1 = DHT22_ReadByte();
        Rh_byte2 = DHT22_ReadByte();
        Temp_byte1 = DHT22_ReadByte();
        Temp_byte2 = DHT22_ReadByte();
        sum = DHT22_ReadByte();

        RH = (Rh_byte1 << 8) | Rh_byte2;
        TEMP = (Temp_byte1 << 8) | Temp_byte2;

        *humidity = RH / 10.0;
        if (TEMP & 0x8000)
        {
            TEMP &= 0x7FFF;
            *temperature = -((float)TEMP / 10.0);
        }
        else
        {
            *temperature = (float)TEMP / 10.0;
        }

        return DHT22_OK;
    }

    return DHT22_ERROR;
}
