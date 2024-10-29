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

#include <libmultigot.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int ac __unused, char **av)
{
	int val;

	/* Discard argv0. */
	av++;

	if (*av != NULL) {
		val = atoi(*av);
		printf("Setting counter to %d\n", val);
		set_counter(val);
		av++;
		printf("%s\n", counter_str("set"));
	}

	if (*av != NULL) {
		val = atoi(*av);
		printf("Decrementing by %d\n", val);
		decrement_counter(val);
		av++;
		printf("%s\n", counter_str("decrement"));
	}

	if (*av != NULL) {
		val = atoi(*av);
		printf("Incrementing by %d\n", val);
		increment_counter(val);
		av++;
		printf("%s\n", counter_str("increment"));
	}

	printf("%s\n", counter_str("final"));
	return (0);
}
