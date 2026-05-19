/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <soc.h>
#include <abstract/gpio.h>

/*
 * Bootloader version.
 */
#define CONF_BT_VERSION 0x01

/*
 * Comment this out to use HSI clock.
 */
#define CONF_CLK_SOURCE_HSE

/*
 * Defines the start of the user flash area.
 */
#define CONF_USER_RESET_ADDR 0x8400

/*
 * Refer to RM0016, Section 22.3.4, Table 54 for derivation.
 * Calculated for 115200 bps @ 16MHz.
 */
#define CONF_UART_DIV 0x008B

/*
 * GPIO configuration for the external jumper.
 */
#define CONF_PORT GPIOD
#define CONF_PIN  GPIO_PIN_2

/*
 * Synchronization byte used by the host to
 * initiate communication.
 */
#define CONF_SYNCH 0x7F

/*
 * Protocol responses.
 */
#define CONF_ACK  0x79 /* positive acknowledge */
#define CONF_NACK 0x1F /* negative acknowledge */

/*
 * Retrieve bootloader version and supported command set.
 */
#define CONF_GET_CMD 0x00

/*
 * This follows the N-1 convention.
 */
#define CONF_GET_CMD_BYTE_COUNT 0x01

#endif /* CONFIG_H */
