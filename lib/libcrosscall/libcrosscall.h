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

#ifndef __LIBCROSSCALL_H__
#define	__LIBCROSSCALL_H__

typedef unsigned int (rng_func_t)(void);

unsigned int	one_value(unsigned int);
unsigned int	two_value(unsigned int);
rng_func_t	*one_func(void);
rng_func_t	*two_func(void);

#endif /* !__LIBCROSSCALL_H__ */
