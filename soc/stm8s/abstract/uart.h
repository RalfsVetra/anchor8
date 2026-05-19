/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef STM8S_ABSTRACT_UART_H
#define STM8S_ABSTRACT_UART_H

#include <soc.h>

#if defined(STM8S103) || defined(STM8S003)
#define UARTX                  UART1
#endif

/*
 * UART1 is used here as a generic reference. The register structure is
 * consistent across all UART peripherals, allowing these definitions
 * to be reused without duplicating code.
 */
#define UARTX_SR_OR            UART1_SR_OR
#define UARTX_SR_PE            UART1_SR_PE
#define UARTX_SR_NF            UART1_SR_NF
#define UARTX_SR_FE            UART1_SR_FE
#define UARTX_SR_TC            UART1_SR_TC
#define UARTX_SR_TXE           UART1_SR_TXE
#define UARTX_SR_RXNE          UART1_SR_RXNE

#define UARTX_CR2_TEN          UART1_CR2_TEN
#define UARTX_CR2_REN          UART1_CR2_REN
#define UARTX_CR1_PCEN         UART1_CR1_PCEN

#define UARTX_CR1_RESET_VALUE  UART1_CR1_RESET_VALUE
#define UARTX_CR2_RESET_VALUE  UART1_CR2_RESET_VALUE
#define UARTX_BRR1_RESET_VALUE UART1_BRR1_RESET_VALUE
#define UARTX_BRR2_RESET_VALUE UART1_BRR2_RESET_VALUE

#endif /* STM8S_ABSTRACT_UART_H */
