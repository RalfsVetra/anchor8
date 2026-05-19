/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#include "protocol.h"

#include <soc.h>
#include <config.h>
#include <anchor8/drivers/uart.h>

uint8_t proto_receive(void)
{
	while(TRUE) {
		uint8_t byte_cmd, byte_cmp;

		/*
		 * Wait for the command and its bitwise complement.
		 */
		if (!uart_recv_byte(&byte_cmd)) continue;
		if (!uart_recv_byte(&byte_cmp)) continue;

		/*
		 * Validate using 1's complement check.
		 */
		if (byte_cmd != (uint8_t)~byte_cmp) {
			uart_send_byte(CONF_NACK);
			continue;
		}

		uart_send_byte(CONF_ACK);
		return byte_cmd;
	}
}

static void proto_handle_get(void)
{
	uart_send_byte(CONF_GET_CMD_BYTE_COUNT);
	uart_send_byte(CONF_BT_VERSION);
	uart_send_byte(CONF_GET_CMD);
	uart_send_byte(CONF_ACK);
}

void proto_process(uint8_t cmd)
{
	switch(cmd) {
	case CONF_GET_CMD:
		proto_handle_get();
		break;
	default:
		break;
	}
}
