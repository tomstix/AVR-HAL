#include "gpio.h"

void gpio_set_dir(const gpio_t *gpio, const gpio_direction_t dir)
{
    if (dir == GPIO_OUTPUT)
    {
        *gpio->ddr |= (1 << gpio->pin_number);
    }
    else
    {
        *gpio->ddr &= ~(1 << gpio->pin_number);
    }

}

void gpio_write(const gpio_t *gpio, const bool value)
{
    if (value)
    {
        *gpio->port |= (1 << gpio->pin_number);
    }
    else
    {
        *gpio->port &= ~(1 << gpio->pin_number);
    }
}

uint8_t gpio_read(const gpio_t *gpio)
{
    return (*gpio->pin & (1 << gpio->pin_number)) >> gpio->pin_number;
}