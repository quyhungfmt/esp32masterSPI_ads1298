

#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "soc/rtc_periph.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_timer.h"
#include "driver/gpio.h"
#include "esp_intr_alloc.h"

#include "Master_spi.h"
#include "sdkconfig.h"



#define FullT = 5 //(ns)


    spi_device_handle_t handle;

void ADS_setup()
{
    ESP_LOGI("---------", "----------------------\n");
    ESP_LOGI("ADS_SETUP", "ADS BEGIN SETUP");
    spi_bus_config_t busconfig = {
        .sclk_io_num = GPIO_SCLK,
        .mosi_io_num = GPIO_MOSI,
        .miso_io_num = GPIO_MISO,
        .quadhd_io_num = -1,
        .quadwp_io_num = -1,
    };

    spi_device_interface_config_t devcfg = {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .clock_speed_hz = CLOCK2,
        .duty_cycle_pos = 128, // 50% duty cycle
        .mode = 1,
        .spics_io_num = GPIO_CS,
        .cs_ena_posttrans = 3, // Keep the CS low 3 cycles after transaction
        .queue_size = 3};
    spi_bus_initialize(VSPI_HOST, &busconfig, 1);
    spi_bus_add_device(VSPI_HOST, &devcfg, &handle);
    ESP_LOGI("ADS_SETUP", "SETUP!!");
}

void ADS_send(spi_transaction_t t, uint8_t data_send){
    memset(&t,0,sizeof(t));
    t.length = 8;
    t.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
    t.tx_data[0] = data_send;
    spi_device_polling_transmit(handle,&t);
    printf("SET OPCODE: 0x%02x \n",t.tx_data[0]);
}

void ADS_get( spi_transaction_t t,uint8_t data[],char *tx){
    char mess[20];
    sprintf(mess,"%s",tx);
    memset(&t,0,sizeof(t));
    t.flags = SPI_TRANS_USE_RXDATA|SPI_TRANS_USE_TXDATA;
    t.length = 24;
    t.rxlength = 24;
    spi_device_polling_transmit(handle,&t);
    data[0] = t.rx_data[0];
    data[1] = t.rx_data[1];
    data[2] = t.rx_data[2];
    printf("%s : 0X%02X - 0X%02X - 0X%02X \n",mess,data[0],data[1],data[2]);
}
void showdata(uint8_t data[]) {
        printf("data: 0x%02x - 0x%02x - 0x%02x \n",data[0],data[1],data[2]);
}







// int showdata(uint8_t data[],char *filename)
// {
//     char Filepath[256];
//     FILE *file;
//     sprintf(Filepath,"C:\\Users\\NGUYEN HUNG CTU\\Documents\\DATA_ADS1298\\%s",filename);
//     printf("data: 0x%02x - 0x%02x - 0x%02x \n", data[0], data[1], data[2]);
//     file = fopen(Filepath, "w");
//     if (file == NULL) {
//         printf("Không thể tạo file.\n");
//         return 0;
//     }
//     fprintf(file,"---------%s---------\nDATA : 0x%02x - 0x%02x - 0x%02x",filename,data[0],data[1],data[2]);
//     fclose(file);
//     return 1;
// }








// void ADS_command(spi_transaction_t t,uint8_t data_out)
// {
//     memset(&t,0,sizeof(t));
//     trans.length = 8;
//     trans.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA | SPI_TRANS_CS_KEEP_ACTIVE | SPI_TRANS_MODE_OCT;
//     trans.tx_data[0] = data_out;
//     ret = spi_device_transmit(handle, &trans);
//     printf("MASTER SEND : 0x%02x \n", data_out);
//     (ret == 0) ? printf("ESP OK\n") : printf("err");
//     /*
//     ------------------------------------------------------------
//     WAKEUP  -> 0000 0010    0X02
//     STANBDY -> 0000 0100    0X04
//     RESET   -> 0000 0110    0X06
//     START   -> 0000 1000    0X08
//     STOP    -> 0000 1010    0X0A
//     ------------------------------------------------------------
//     RDATAC (read data continuous mode)      -> 0001 0000    0x10
//     SDATAC (stop read data continuos mode)  -> 0001 0001    0x11
//     RDATA (read data by command)            -> 0001 0010    0x12
//     ------------------------------------------------------------
//     RREG (read n nnnn register starting at address r rrrr)
//     FIRST BYTE                  SECOND BYTE
//     001r rrrr                   000n nnnn
//     WREG (write n nnnn regiser starting at address r rrrr)
//     FIRST BYTE                  SECOND BYTE
//     010r rrrr                   000n nnnn
//     ------------------------------------------------------------
//     */
// }














// void ADS_read()
// {
//     gpio_set_level(GPIO_NUM_5, 0);
//     vTaskDelay(1 / portTICK_PERIOD_MS);
//     uint8_t data;
//     uint8_t data1;
//     uint8_t data2;
//     uint8_t data3;
//     memset(&trans, 0, sizeof(trans));
//     data = trans.rx_data[0];
//     data1 = trans.rx_data[1];
//     data2 = trans.rx_data[2];
//     printf("DATA READ 8  :0X%02X \n", data);
//     printf("DATA READ 16 :0X%02X \n", data1);
//     printf("DATA READ 24 :0X%02X \n", data2);
//     vTaskDelay(1000 / portTICK_PERIOD_MS);
// }

// void ADS_end()
// {
//     gpio_set_level(GPIO_SCLK, 0);
//     gpio_set_level(GPIO_CS, 1);
// }

// uint8_t ADS_transfer(uint8_t byte_out)
// {
//     printf("delay1:\n");
//     delay_ns(500000);
//     printf("delay2:\n");
//     return byte_out;
// }

// void delay_ns(uint32_t ns)
// {
//     esp_timer_handle_t timer;
//     esp_timer_create_args_t timer_args = {
//         .callback = NULL,
//         .name = "delay_timer"};
//     esp_timer_create(&timer_args, &timer);
//     esp_timer_start_once(timer, ns);
// }

// uint8_t byte_in = 0;
// uint8_t i ,r;
// for(i = 0x80;i>0;i=i>>1){
//     r = byte_out & i; // (0 = false)
//     gpio_set_level(GPIO_MOSI,r);
// }
// return byte_in;

// void delay_ns(uint32_t ns) {
//     esp_timer_handle_t timer;
//     esp_timer_create_args_t timer_args = {
//         .callback = NULL,
//         .name = "delay_timer"
//     };
//     esp_timer_create(&timer_args, &timer);
//     esp_timer_start_once(timer, ns);
// }

// void ADS_setup() {
//     gpio_set_direction(GPIO_MOSI,GPIO_MODE_OUTPUT);
//     gpio_set_direction(GPIO_MISO,GPIO_MODE_INPUT);

//     gpio_set_level(GPIO_SCLK,0);
//     gpio_set_direction(GPIO_SCLK,GPIO_MODE_OUTPUT);

//     gpio_set_level(GPIO_CS,1);
//     gpio_set_direction(GPIO_CS,GPIO_MODE_OUTPUT);

//     gpio_set_level(GPIO_START,0);
//     gpio_set_direction(GPIO_START,GPIO_MODE_OUTPUT);
// }
// void ADS_begin() {
//     gpio_set_level(GPIO_CS,0);
// }
// void ADS_end(){
//     gpio_set_level(GPIO_SCLK,0);
//     gpio_set_level(GPIO_CS,1);

// }

// uint8_t ADS_transfer(uint8_t byte_out) {
//     uint8_t byte_in = 0;
//     uint8_t i ,r;
//     for(i = 0x80;i>0;i=i>>1){
//         r = byte_out & i; // (0 = false)
//         gpio_set_level(GPIO_MOSI,r);
//     }
//     return byte_in;
// }