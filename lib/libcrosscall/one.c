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
one_value(unsigned int addend)
{
	return (dice_roll() + addend);
}

rng_func_t *
one_func(void)
{
	return (dice_roll);
}
