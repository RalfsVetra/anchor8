/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#include <soc.h>
#include <abstract/uart.h>
#include <anchor8/drivers/uart.h>

bool uart_recv_byte(uint8_t *buffer)
{
	/*
	 * The received data is ready to be read.
	 */
	while(!(UARTX->SR & UARTX_SR_RXNE));

	/*
	 * Check for overrun, parity, noise
	 * or framing error.
	 */
	if ((UARTX->SR & UARTX_SR_OR) ||
	    (UARTX->SR & UARTX_SR_PE) ||
	    (UARTX->SR & UARTX_SR_NF) ||
	    (UARTX->SR & UARTX_SR_FE)) {
		*buffer = UARTX->DR;

		return FALSE;
	}

	*buffer = UARTX->DR;
	return TRUE;
}

void uart_send_byte(uint8_t data)
{
	/*
	 * Wait until the TX is empty.
	 */
	while(!(UARTX->SR & UARTX_SR_TXE));

	UARTX->DR = data;

	/*
	 * Wait for transmission complete.
	 */
	while(!(UARTX->SR & UARTX_SR_TC));
}
