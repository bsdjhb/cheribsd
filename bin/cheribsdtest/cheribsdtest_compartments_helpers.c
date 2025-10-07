/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2025 John Baldwin
 *
 * This software was developed by SRI International, the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology), and Capabilities Limited under Defense Advanced Research
 * Projects Agency (DARPA) Contract No. FA8750-24-C-B047 ("DEC").
 */

#include <unistd.h>

#include "cheribsdtest.h"
#include "cheribsdtest_compartments.h"

static char compartment_one_data_buffer[1024];

void *
compartment_one_static_data_ptr(void)
{
	return (compartment_one_data_buffer);
}

void *
compartment_two_static_data_ptr(void)
{
	return (compartment_one_data_buffer);
}

#ifdef CHERIBSD_DYNAMIC_TESTS
void *
compartment_one_global_data_ptr(void)
{
	return (&optarg);
}

void *
compartment_two_global_data_ptr(void)
{
	return (&optarg);
}
#endif
