/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2024 Ararat River Consulting, LLC
 *
 * This software was developed by SRI International, the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology), and Capabilities Limited under Defense Advanced Research
 * Projects Agency (DARPA) Contract No. FA8750-24-C-B047 ("DEC").
 */

#include "libcrosscall.h"

#include "internal.h"

unsigned int
two_value(unsigned int orend)
{
	return (dice_roll() | orend);
}

rng_func_t *
two_func(void)
{
	return (dice_roll);
}
