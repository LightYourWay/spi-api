/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_SPI_H__
#define __STM32_SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <assert.h>
#include "spi_api.h"
#include "spi.h"

    class spi_port
    {
        SPI_TypeDef *port;
        SPI_InitTypeDef *port_config;

    public:
        SPI_HandleTypeDef handle;

        spi_port(SPI_TypeDef *port);

        void init(SPI_InitTypeDef *device_config);
        void checkout(SPI_InitTypeDef *device_config);
    };

    class spi_device : public spi_api
    {
        spi_port *port;
        SPI_InitTypeDef *device_config;
        GPIO_TypeDef *nss_port;
        uint16_t nss_pin;

    public:
        spi_device(spi_port *port, SPI_InitTypeDef *device_config, GPIO_TypeDef *nss_port, uint16_t nss_pin);

        void start() override;

        void stop() override;

        void sendByte(uint8_t byte) override;

        uint8_t receiveByte() override;
    };

#ifdef __cplusplus
}
#endif

#endif /* __STM32_SPI_H__ */