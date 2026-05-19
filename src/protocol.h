/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <soc.h>

uint8_t proto_receive(void);
void proto_process(uint8_t cmd);

#endif /* PROTOCOL_H */
