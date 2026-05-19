/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ANCHOR8_DRIVERS_GPIO_H
#define ANCHOR8_DRIVERS_GPIO_H

#include <soc.h>
#include <abstract/gpio.h>

/*
 * Set pin to input mode with internal pull-up resistor enabled.
 * Disable external interrupts to avoid spurious interrupts.
 */
static inline void gpio_init(GPIO_TypeDef *gpio, GPIO_Pin_TypeDef pin)
{
        gpio->DDR &= ~pin;
	gpio->CR1 |= pin;
	gpio->CR2 &= ~pin;
}

/*
 * Reset the provided GPIO port.
 */
static inline void gpio_reset(GPIO_TypeDef *gpio)
{
	gpio->ODR = GPIO_ODR_RESET_VALUE;
	gpio->DDR = GPIO_DDR_RESET_VALUE;
	gpio->CR1 = GPIO_CR1_RESET_VALUE;
	gpio->CR2 = GPIO_CR2_RESET_VALUE;
}

#endif /* ANCHOR8_DRIVERS_GPIO_H */
