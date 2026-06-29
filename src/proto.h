/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef PROTO_H
#define PROTO_H

#include <soc.h>

uint8_t proto_receive(void);
void proto_process(uint8_t cmd);

#endif /* PROTO_H */
