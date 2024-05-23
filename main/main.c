
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


#define GPIO_MOSI 23
#define GPIO_MISO 19
#define GPIO_SCLK 18
#define GPIO_CS 5
#define GPIO_START 2

uint8_t opcode[3];
uint8_t channel1[3];
uint8_t channel2[3];
uint8_t channel3[3];
uint8_t channel4[3];
uint8_t channel5[3];
uint8_t channel6[3];
uint8_t channel7[3];
uint8_t channel8[3];
// Main application

    spi_transaction_t t;
void app_main(void)
{
    memset(&t, 0, sizeof(t));
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_2,1);
    ESP_LOGI("START","LED 2 HIGH \n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    gpio_set_level(GPIO_NUM_2,0);
    ESP_LOGI("START","LED 2 LOW \n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    

    printf("Master input:\n");
        // int i = 0;
        // t.flags =  SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
        // t.length =  16;
        // t.tx_data[0] = 0X08; // start
        // t.tx_data[1] = 0x10;
        // printf("data send[0] = 0x%02x \n",t.tx_data[0]);
        // printf("data send[1] = 0x%02x \n",t.tx_data[1]);
        // spi_device_polling_transmit(handle, &t);
    ADS_setup();
    ADS_send(t,START);
    ADS_send(t,RDATAC);
    while (1)
    {
        ADS_get(t,opcode,"opcode");
        ADS_get(t,channel1,"CHANNEL1");    
        ADS_get(t,channel2,"CHANNEL2");
        ADS_get(t,channel3,"CHANNEL3");
        ADS_get(t,channel4,"CHANNEL4");
        ADS_get(t,channel5,"CHANNEL5");
        ADS_get(t,channel6,"CHANNEL6");
        ADS_get(t,channel7,"CHANNEL7");
        ADS_get(t,channel8,"CHANNEL8");
        printf("\n");
        printf("\n");
        vTaskDelay(200/portTICK_PERIOD_MS);


        // t.length = 8;
        // t.rxlength = 8;
        // printf("data get[0]  = 0x%02x \n",t.rx_data[0]);
        // spi_device_polling_transmit(handle, &t);
        // vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}
