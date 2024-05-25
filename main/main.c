
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
#include "driver/timer.h"

#include "outputPin.h"
#include "Master_spi.h"
#include "sdkconfig.h"
// Pins in use

#define GPIO_MOSI 23
#define GPIO_MISO 19
#define GPIO_SCLK 18
#define GPIO_CS 5
#define GPIO_START 2

int idex = 27 * 500;
uint8_t opcode[13500];
uint8_t channel1[3];
uint8_t channel2[3];
uint8_t channel3[3];
uint8_t channel4[3];
uint8_t channel5[3];
uint8_t channel6[3];
uint8_t channel7[3];
uint8_t channel8[3];

spi_transaction_t t;
// void task1(void *pvParameter){
//     while(1)
//     {
//         ADS_get(t, opcode);
//         printf("\n");
//     }
// }
void app_main(void)
{
    memset(opcode, 0, sizeof(opcode));
    memset(&t, 0, sizeof(t));
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_2, 1);
    ESP_LOGI("START", "LED 2 HIGH \n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(GPIO_NUM_2, 0);
    ESP_LOGI("START", "LED 2 LOW \n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Master input:\n");
    ADS_setup(CLOCK2);
    printf("setup:\n");
    ADS_send(t, START);
    printf("setup start:\n");
    ADS_send(t, RDATAC);
    char titles[9][10] = {"OPCODE", "CHANNEL1", "CHANNEL2", "CHANNEL3", "CHANNEL4", "CHANNEL5", "CHANNEL6", "CHANNEL7", "CHANNEL8"};
    int i = 0;
    vTaskDelay(100/portTICK_PERIOD_MS);
    ADS_get(t, opcode);
    gpio_set_level(GPIO_NUM_2, 1);
    ESP_LOGI("DATA ", "DONE!!!!");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    for (int x = 0, j = 0, c = 1; x < 27 * 500; x += 3, j++)
    {
        printf("%s : 0x%02x - 0x%02x - 0x%02x \n", titles[j], opcode[(x)], opcode[(x + 1)], opcode[(x + 2)]);
        if (j == 8)
        {
            j = -1;
            printf("mẫu :%d \n\n", ++c);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    // xTaskCreate(&task1,"ads_get",2048,NULL,2,NULL);
    // while (1)
    // {
    //     while (++i < 1000)
    //     {
    //         ADS_get(t, opcode);
    //         printf("\n");
    //         printf("\n");
    //         vTaskDelay(10 / portTICK_PERIOD_MS);
    //         /* code */
    //     }
    //     gpio_set_level(GPIO_NUM_2, 1);
    //     ESP_LOGI("START", "LED 2 HIGH \n");
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     gpio_set_level(GPIO_NUM_2, 0);
    //     ESP_LOGI("START", "LED 2 LOW \n");
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     // t.length = 8;
    //     // t.rxlength = 8;
    //     // printf("data get[0]  = 0x%02x \n",t.rx_data[0]);
    //     // spi_device_polling_transmit(handle, &t);
    //     // vTaskDelay(1 / portTICK_PERIOD_MS);
    // }
    /* code */
}
