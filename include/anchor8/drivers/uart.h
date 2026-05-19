/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ANCHOR8_DRIVERS_UART_H
#define ANCHOR8_DRIVERS_UART_H

#include <soc.h>
#include <abstract/uart.h>

void uart_send_byte(uint8_t data);
bool uart_recv_byte(uint8_t *buffer);

static inline void uart_init(uint16_t uart_div)
{
	/*
	 * Enable parity control.
	 */
	UARTX->CR1 |= UARTX_CR1_PCEN;

	/*
	 * Activate both transmitter and receiver.
	 */
	UARTX->CR2 |= (UARTX_CR2_TEN | UARTX_CR2_REN);

	/*
	 * Refer to RM0016, Section 22.3.4 for the mapping
	 * of the 16-bit divisor.
	 */
	UARTX->BRR2 = ((uart_div >> 8) & 0xF0) + (uart_div & 0x0F);
	UARTX->BRR1 = (uart_div >> 4) & 0xFF;
}

static inline void uart_reset(void)
{
	UARTX->CR1  = UARTX_CR1_RESET_VALUE;
	UARTX->CR2  = UARTX_CR2_RESET_VALUE;
	UARTX->BRR1 = UARTX_BRR1_RESET_VALUE;
	UARTX->BRR2 = UARTX_BRR2_RESET_VALUE;
}

#endif /* ANCHOR8_DRIVERS_UART_H */
