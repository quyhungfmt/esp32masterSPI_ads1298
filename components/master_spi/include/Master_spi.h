#include <stdio.h>
#include <stdint.h>

#define CLOCK1  1000000 //1MHz
#define CLOCK2  2000000 //1MHz
#define CLOCK3  3000000 //1MHz
#define CLOCK4  4000000 //1MHz
#define CLOCK5  5000000 //1MHz
#define CLOCK6  6000000 //1MHz
#define CLOCK7  7000000 //1MHz
#define CLOCK8  8000000 //1MHz
#define CLOCK9  9000000 //1MHz
#define CLOCK10 10000000 //1MHz
#define CLOCK11 11000000 //1MHz


#define WAKEUP 0x02
#define STANDBY 0x04
#define RESET 0x06
#define START 0x08
#define STOP 0x0A
#define RDATAC 0x10
#define SDATAC 0x11
#define RDATA 0x12

#define GPIO_MOSI GPIO_NUM_23
#define GPIO_MISO GPIO_NUM_19 // 19
#define GPIO_SCLK GPIO_NUM_18 // 18
#define GPIO_CS GPIO_NUM_5
#define GPIO_START GPIO_NUM_2


// void ADS_setup();
// void ADS_command(uint8_t byte_out);
// void ADS_read();
// void ADS_end();
// void delay_ns(uint32_t ns);
// uint8_t ADS_transfer(uint8_t byte_out);

void ADS_setup(spi_device_handle_t handle);
void ADS_send(spi_device_handle_t handle,spi_transaction_t t, uint8_t data_send);
void ADS_get(spi_device_handle_t handle, spi_transaction_t t,uint8_t data[]);