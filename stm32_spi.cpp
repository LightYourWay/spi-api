#include "stm32_spi.h"

spi_device::spi_device(spi_port *port, SPI_InitTypeDef *device_config, GPIO_TypeDef *nss_port, uint16_t nss_pin) : port(port), device_config(device_config), nss_port(nss_port), nss_pin(nss_pin)
{
    port->init(device_config);
};

void spi_device::start()
{
    port->checkout(device_config);
    HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_RESET);
}

void spi_device::stop()
{
    HAL_GPIO_WritePin(nss_port, nss_pin, GPIO_PIN_SET);
}

void spi_device::sendByte(uint8_t byte)
{
    HAL_SPI_Transmit(&(port->handle), &byte, 1, HAL_MAX_DELAY);
}

uint8_t spi_device::receiveByte()
{
    uint8_t byte;
    HAL_SPI_Receive(&(port->handle), &byte, 1, HAL_MAX_DELAY);
    return byte;
}

spi_port::spi_port(SPI_TypeDef *port) : port(port)
{
    handle.Instance = port;
};

void spi_port::checkout(SPI_InitTypeDef *device_config)
{
    if (port_config != device_config)
    {
        init(device_config);
    }
};

void spi_port::init(SPI_InitTypeDef *device_config)
{
    port_config = device_config;
    handle.Init = *device_config;
    if (HAL_SPI_Init(&handle) != HAL_OK)
    {
        Error_Handler();
    }
}