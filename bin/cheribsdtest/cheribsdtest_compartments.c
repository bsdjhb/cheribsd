/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2025 John Baldwin
 *
 * This software was developed by SRI International, the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology), and Capabilities Limited under Defense Advanced Research
 * Projects Agency / Air Force Research Laboratory (DARPA/AFRL) Contract
 * No. FA8750-24-C-B047 ("DEC").
 */

#include <cheri/cheric.h>

#include "cheribsdtest.h"
#include "cheribsdtest_compartments.h"

static void
compartment_one_foo(void)
{
}

static void
compartment_two_foo(void)
{
}

static void
assert_disjoint_bounds(void *one, void *two, const char *label_one,
    const char *label_two)
{
	CHERIBSDTEST_VERIFY2(
	    !cheri_is_address_inbounds(one, cheri_base_get(two)) &&
	    !cheri_is_address_inbounds(two, cheri_base_get(one)),
	    "%#p (%s) and %#p (%s) overlap", one, label_one, two, label_two);
}

CHERIBSDTEST(compartment_pcc_bounds,
    "Check that PCC bounds of sub-object compartments are disjoint")
{
	assert_disjoint_bounds(&compartment_one_foo, &compartment_two_foo,
	    "compartment_one_foo", "compartment_two_foo");
	assert_disjoint_bounds(&compartment_one_foo, &compartment_pcc_bounds,
	    "compartment_one_foo", "compartment_pcc_bounds");
	assert_disjoint_bounds(&compartment_two_foo, &compartment_pcc_bounds,
	    "compartment_two_foo", "compartment_pcc_bounds");
	cheribsdtest_success();
}

#define	CHERI_PERM_STORE_MASK						\
	(CHERI_PERM_STORE | CHERI_PERM_STORE_CAP | CHERI_PERM_STORE_LOCAL_CAP)

CHERIBSDTEST(compartment_static_cap_perms,
    "Check that ACLs constrain permissions for pointers to non-preemptible "
    "variables")
{
	void *one = compartment_one_static_data_ptr();
	void *two = compartment_two_static_data_ptr();

        CHERIBSDTEST_VERIFY((cheri_getperm(one) & CHERI_PERM_STORE_MASK) ==
	    CHERI_PERM_STORE_MASK);
	CHERIBSDTEST_VERIFY((cheri_getperm(two) & CHERI_PERM_STORE_MASK) == 0);
	CHERIBSDTEST_VERIFY(cheri_equal_exact(cheri_clearperm(one,
	    CHERI_PERM_STORE_MASK), two));
	cheribsdtest_success();
}

#ifdef CHERIBSD_DYNAMIC_TESTS
CHERIBSDTEST(compartment_global_cap_perms,
    "Check that ACLs constrain permissions for pointers to preemptible "
    "variables")
{
	void *one = compartment_one_global_data_ptr();
	void *two = compartment_two_global_data_ptr();

        CHERIBSDTEST_VERIFY((cheri_getperm(one) & CHERI_PERM_STORE_MASK) ==
	    CHERI_PERM_STORE_MASK);
	CHERIBSDTEST_VERIFY((cheri_getperm(two) & CHERI_PERM_STORE_MASK) == 0);
	CHERIBSDTEST_VERIFY(cheri_equal_exact(cheri_clearperm(one,
	    CHERI_PERM_STORE_MASK), two));
	cheribsdtest_success();
}
#endif
