
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "lwip/igmp.h"

#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "soc/rtc_periph.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "esp_spi_flash.h"

#include "driver/gpio.h"
#include "esp_intr_alloc.h"

#include "outputPin.h"
#include "Master_spi.h"
#include "sdkconfig.h"
// Pins in use




// Pins in use
#define GPIO_MOSI 23
#define GPIO_MISO 19
#define GPIO_SCLK 18
#define GPIO_CS 5
#define GPIO_START 2
// Main application
void app_main(void)
{
    spi_device_handle_t handle;

    // Configuration for the SPI bus
    spi_bus_config_t buscfg = {
        .mosi_io_num = GPIO_MOSI,
        .miso_io_num = GPIO_MISO,
        .sclk_io_num = GPIO_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1};

    // Configuration for the SPI device on the other side of the bus
    spi_device_interface_config_t devcfg = {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .clock_speed_hz = 2000000,
        .duty_cycle_pos = 128, // 50% duty cycle
        .mode = 1,
        .spics_io_num = GPIO_CS,
        .cs_ena_posttrans = 3, // Keep the CS low 3 cycles after transaction
        .queue_size = 3};

    spi_bus_initialize(VSPI_HOST, &buscfg, SPI_DMA_CH_AUTO);
    spi_bus_add_device(VSPI_HOST, &devcfg, &handle);
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    uint8_t senddata = 0xf0;
    uint8_t getdata = 0xff;

    printf("Master input:\n");
    int i = 0;
        t.flags =  SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
        t.length =  16;
        t.tx_data[0] = 0X08; // start
        t.tx_data[1] = 0x10;
        printf("data send[0] = 0x%02x \n",t.tx_data[0]);
        printf("data send[1] = 0x%02x \n",t.tx_data[1]);
        spi_device_polling_transmit(handle, &t);
    while (1)
    {
        t.length = 8;
        t.rxlength = 8;
        printf("data get[0]  = 0x%02x \n",t.rx_data[0]);
        spi_device_polling_transmit(handle, &t);
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}
