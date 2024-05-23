

#include "esp_err.h"
#include "driver/gpio.h"



void pinModeOut(gpio_num_t gpio_pin);
void digitalWrite(gpio_num_t gpio_pin, int stt);
void digitalToggle(gpio_num_t gpio_pin);