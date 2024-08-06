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

#ifndef __LIBMULTIGOT_H__
#define	__LIBMULTIGOT_H__

void	set_counter(int);
void	decrement_counter(int);
void	increment_counter(int);
const char *counter_str(const char *);

#endif /* !__LIBMULTIGOT_H__ */
