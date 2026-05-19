/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#include <config.h>

/*
 * Should be the name of a dummy interrupt routine
 * in order to catch properly unexpected interrupts.
 */
#define NULL 0

#define REDIRECT_VECTOR(i) ((void (*)())(CONF_USER_RESET_ADDR + ((i) * 4)))

extern void _stext(); /* startup routine */

#pragma section const {vector}

void (* const @vector _vectab[32])() = {
	_stext,                 /* RESET       */
	REDIRECT_VECTOR(1),	/* TRAP        */
	REDIRECT_VECTOR(2),	/* TLI         */
	REDIRECT_VECTOR(3),	/* AWU         */
	REDIRECT_VECTOR(4),	/* CLK         */
	REDIRECT_VECTOR(5),	/* EXTI PORTA  */
	REDIRECT_VECTOR(6),	/* EXTI PORTB  */
	REDIRECT_VECTOR(7),	/* EXTI PORTC  */
	REDIRECT_VECTOR(8),	/* EXTI PORTD  */
	REDIRECT_VECTOR(9),	/* EXTI PORTE  */
	REDIRECT_VECTOR(10),	/* CAN RX      */
	REDIRECT_VECTOR(11),	/* CAN TX      */
	REDIRECT_VECTOR(12),	/* SPI         */
	REDIRECT_VECTOR(13),	/* TIMER 1 OVF */
	REDIRECT_VECTOR(14),	/* TIMER 1 CAP */
	REDIRECT_VECTOR(15),	/* TIMER 2 OVF */
	REDIRECT_VECTOR(16),	/* TIMER 2 CAP */
	REDIRECT_VECTOR(17),	/* TIMER 3 OVF */
	REDIRECT_VECTOR(18),	/* TIMER 3 CAP */
	REDIRECT_VECTOR(19),	/* USART TX    */
	REDIRECT_VECTOR(20),	/* USART RX    */
	REDIRECT_VECTOR(21),	/* I2C         */
	REDIRECT_VECTOR(22),	/* LINUART TX  */
	REDIRECT_VECTOR(23),	/* LINUART RX  */
	REDIRECT_VECTOR(24),	/* ADC         */
	REDIRECT_VECTOR(25),	/* TIMER 4 OVF */
	REDIRECT_VECTOR(26),	/* EEPROM ECC  */
	REDIRECT_VECTOR(27),	/* Reserved    */
	REDIRECT_VECTOR(28),	/* Reserved    */
	REDIRECT_VECTOR(29),	/* Reserved    */
	REDIRECT_VECTOR(30),	/* Reserved    */
	REDIRECT_VECTOR(31),	/* Reserved    */
};
