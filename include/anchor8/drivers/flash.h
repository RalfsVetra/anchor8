/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ANCHOR8_DRIVERS_FLASH_H
#define ANCHOR8_DRIVERS_FLASH_H

#include <soc.h>
#include <abstract/flash.h>

static inline void flash_unlock_prog(void)
{
	FLASH->PUKR = FLASH_RASS_KEY1;
	FLASH->PUKR = FLASH_RASS_KEY2;
}

static inline void flash_lock_prog(void)
{
	FLASH->IAPSR = ~FLASH_IAPSR_PUL;
}

static inline void flash_unlock_data(void)
{
	FLASH->DUKR = FLASH_RASS_KEY2;
	FLASH->DUKR = FLASH_RASS_KEY1;
}

static inline void flash_lock_data(void)
{
	FLASH->IAPSR = ~FLASH_IAPSR_DUL;
}

static inline void flash_lock_mem(void)
{
	flash_lock_prog();
	flash_lock_data();
}

#endif /* ANCHOR8_DRIVERS_FLASH_H */
