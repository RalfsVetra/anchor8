/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ANCHOR8_H
#define ANCHOR8_H

#include <soc.h>
#include <config.h>

typedef void (*JPF)(void);

#define USER_RESET_ADDR ((uint8_t *)CONF_USER_RESET_ADDR)

/*
 * 0x82 and 0xAC are op-codes for
 * INT  and JPF instructions.
 */
#define OP_INT 0x82
#define OP_JPF 0xAC

#endif /* ANCHOR8_H */
