/*
 * SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
 *
 * SPDX-License-Identifier: MIT
 */

#include <soc.h>
#include <abstract/clk.h>
#include <anchor8/platform/hooks.h>

/*
 * Perform hardware initialization after
 * the bootloader has entered the main loop.
 */
void soc_late_init_hook(void)
{
	sim(); /* disable interrupts */

	/*
	 * Set HSI to full speed by clearing prescaler.
	 */
	CLK->CKDIVR = CLK_PRESCALER_HSIDIV1;

#ifdef CONF_CLK_SOURCE_HSE
	/*
	 * Enable clock switching and configure
	 * HSE as the master clock source.
	 */
	CLK->SWCR = CLK_SWCR_SWEN;
	CLK->SWR  = CLK_SOURCE_HSE;

	/*
	 * Stall the SoC until the clock
	 * switching is complete.
	 */
	while(!(CLK->SWCR & CLK_SWCR_SWIF));
#endif /* CONF_CLK_SOURCE_HSE */
}
