/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ANCHOR8_PLATFORM_HOOKS_H
#define ANCHOR8_PLATFORM_HOOKS_H

/*
 * Called right after the bootloader
 * has entered the main loop.
 */
void soc_late_init_hook(void);

#endif /* ANCHOR8_PLATFORM_HOOKS_H */
