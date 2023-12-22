#ifndef __x8_spi_h__
#define __x8_spi_h__

#include "driver/spi.h"
#include "esp_err.h"

esp_err_t spi_transfer(spi_host_t spi, uint8_t *mosi, size_t mosi_len, uint8_t *miso, size_t miso_len);

#endif