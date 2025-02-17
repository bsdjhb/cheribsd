/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2025 Ararat River Consulting, LLC
 *
 * This software was developed by SRI International, the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology), and Capabilities Limited under Defense Advanced Research
 * Projects Agency (DARPA) Contract No. FA8750-24-C-B047 ("DEC").
 */

#include <libcrosscall.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int ac __unused, char **av)
{
	rng_func_t *rng;
	int val;

	/* Discard argv0. */
	av++;

	if (*av != NULL) {
		val = atoi(*av);
		printf("one_value(%d) = %u\n", val, one_value(val));
		av++;
	}

	if (*av != NULL) {
		val = atoi(*av);
		printf("two_value(%d) = %u\n", val, two_value(val));
		av++;
	}

	rng = one_func();
	printf("one_func() = %#p\n", rng);
	printf("two_func() = %#p\n", two_func());

	printf("value is %u\n", rng());
	return (0);
}
