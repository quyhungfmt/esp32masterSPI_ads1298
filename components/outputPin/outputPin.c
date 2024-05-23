#include <stdio.h>
#include <esp_log.h>
#include <driver/gpio.h>
#include "outputPin.h"

void pinModeOut(gpio_num_t gpio_pin)
{
    esp_rom_gpio_pad_select_gpio(gpio_pin);

    gpio_set_direction(gpio_pin, GPIO_MODE_INPUT_OUTPUT);
}

void digitalWrite(gpio_num_t gpio_pin, int stt)
{
    gpio_set_level(gpio_pin, stt);
}

void digitalToggle(gpio_num_t gpio_pin)
{
    int fstt = gpio_get_level(gpio_pin);
    gpio_set_level(gpio_pin, 1-fstt);
}