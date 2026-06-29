/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#include <soc.h>
#include <config.h>
#include <anchor8/drivers/gpio.h>
#include <anchor8/drivers/uart.h>
#include <anchor8/drivers/flash.h>

#include "proto.h"

#define OP_INT 0x82
#define OP_JPF 0xAC
#define USER_RESET_ADDR ((uint8_t *)CONF_USER_RESET_ADDR)

typedef void (*JPF)(void);

int _fctcpy(char name);
static void jump_to_app(void);

int main(void)
{
	/*
	 * Call the specific SoC initialization logic.
	 */
	soc_late_init_hook();
	gpio_init(CONF_PORT, CONF_PIN);

	/*
	 * Check if the activation pin is not pulled to ground.
	 * If high, attempt to boot the existing user application.
	 */
	if ((CONF_PORT->IDR & CONF_PIN) == CONF_PIN) {
		/*
		 * If memory is not virgin, it is considered
		 * as a valid reset vecotr jump.
		 */
		if (*USER_RESET_ADDR == OP_INT ||
		    *USER_RESET_ADDR == OP_JPF) {
			jump_to_app();
		}
	}

	/*
	 * Reset external jumper pin.
	 */
	gpio_reset(CONF_PORT);

	/*
	 * Initialize communication protocol.
	 * TODO: automatically detect the baud rate.
	 */
	uart_init(CONF_UART_DIV);

	/*
	 * The host must send the SYNCH byte to start the session.
	 */
	uint8_t sync_byte;
	if (!uart_recv_byte(&sync_byte) || sync_byte != CONF_SYNCH) {
		uart_send_byte(CONF_NACK);
		jump_to_app();
	}

	/*
	 * TODO: Copy routines to RAM.
	 * Use function _fctcpy().
	 */

	/*
	 * Unlock flash and data memory for the programming session.
	 * Decoupling the unlock from specific commands simplifies the
	 * protocol flow at the cost of having the memory exposed for
	 * the duration of the session.
	 */
	flash_unlock_prog();
	flash_unlock_data();
	uart_send_byte(CONF_ACK);

	while(TRUE) {
		uint8_t cmd = proto_receive();
		proto_process(cmd);
	}
}

/*
 * Cleanup hardware state before handing
 * control to the user application.
 */
static void jump_to_app(void)
{
	uart_reset();
	gpio_reset(CONF_PORT);
	((JPF)USER_RESET_ADDR)();
}
