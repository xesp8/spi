#include <malloc.h>
#include <string.h>

#define MULOF_U32(x) ((x) + (sizeof(uint32_t) - (((x) + sizeof(uint32_t)) % sizeof(uint32_t))))

esp_err_t spi_transfer(spi_host_t spi, uint8_t *mosi, size_t mosi_len, uint8_t *miso, size_t miso_len)
{
    void *miso_buf = NULL, *mosi_buf = NULL;
    if (mosi && mosi_len)
    {
        mosi_buf = malloc(MULOF_U32(mosi_len));
        memcpy(mosi_buf, mosi, mosi_len);
    }

    if (miso && miso_len)
    {
        miso_buf = malloc(MULOF_U32(miso_len));
    }

    spi_trans_t trans = {
        .mosi = mosi_buf,
        .miso = miso_buf,
        .cmd = NULL,
        .addr = NULL,
        .bits = {
            .cmd = 0,
            .addr = 0,
            .miso = miso_len * 8,
            .mosi = mosi_len * 8,
        }};

    esp_err_t ret = spi_trans(spi, &trans);

    if (miso_buf)
    {
        free(miso_buf);
        memcpy(miso, miso_buf, miso_len);
    }

    if (mosi_buf)
        free(mosi_buf);

    return ret;
}