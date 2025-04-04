/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 SRI International
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology) under DARPA contract HR0011-18-C-0016 ("ECATS"), as part of the
 * DARPA SSITH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/counter.h>
#include <sys/jail.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/syscallsubr.h>
#include <sys/sysent.h>
#include <sys/syslog.h>
#include <sys/sysproto.h>

COUNTER_U64_DEFINE_EARLY(flags_captured);
SYSCTL_COUNTER_U64(_security, OID_AUTO, flags_captured, CTLFLAG_RD,
     &flags_captured, "Calls to flag_captured(2)");
COUNTER_U64_DEFINE_EARLY(flags_captured_key);
SYSCTL_COUNTER_U64(_security, OID_AUTO, flags_captured_key, CTLFLAG_RD,
     &flags_captured_key, "Calls to flag_captured(2) with correct key");
COUNTER_U64_DEFINE_EARLY(kernel_flags_captured);
SYSCTL_COUNTER_U64(_security, OID_AUTO, kernel_flags_captured, CTLFLAG_RD,
     &flags_captured, "Calls to flag_captured(9)");
COUNTER_U64_DEFINE_EARLY(kernel_flags_captured_key);
SYSCTL_COUNTER_U64(_security, OID_AUTO, kernel_flags_captured_key, CTLFLAG_RD,
     &flags_captured_key, "Calls to flag_captured(9) with correct key");

void flag_captured(const char *message, uint32_t key);

int
sys_flag_captured(struct thread *td, struct flag_captured_args *uap)
{
	return (kern_flag_captured(td, uap->message, uap->key, __func__));
}

int
kern_flag_captured(struct thread *td, const char * __capability message,
    uint32_t key, const char *source)
{
	struct proc *p = td->td_proc;
	char msg_buf[256];
	char src_buf[32];
	char key_buf[32];
	int error;

	counter_u64_add(flags_captured, 1);

	/*
	 * Try to copy message if it exists but don't return an error
	 * if the pointer is bad (we need to log the event regardless).
	 */
	if (message != NULL) {
		error = copyinstr(message, msg_buf, sizeof(msg_buf), NULL);
		if (error != 0) {
			snprintf(msg_buf, sizeof(msg_buf),
			    "error %d copying from %p", error,
			    (__cheri_fromcap const char *)message);
		}
	} else
		strlcpy(msg_buf, "<null>", sizeof(msg_buf));

	if (source != NULL)
		strlcpy(src_buf, source, sizeof(src_buf));
	else
		strlcpy(src_buf, "<null>", sizeof(src_buf));

	if (key == 0xfe77c0de) {
		counter_u64_add(flags_captured_key, 1);
		strlcpy(key_buf, "correct", sizeof(key_buf));
	} else {
		snprintf(key_buf, sizeof(key_buf), "incorrect (0x%x)",
		    key);
	}

	log(LOG_ALERT,
	    "pid %d (%s), ABI: %s, jid %d, uid %d: captured flag source: (%s) "
	    "message: (%s) key: %s\n", p->p_pid, p->p_comm,
	    p->p_sysent->sv_name, p->p_ucred->cr_prison->pr_id,
	    td->td_ucred->cr_uid, src_buf, msg_buf, key_buf);

	return (0);
}

void
flag_captured(const char *message, uint32_t key)
{
	struct thread *td = curthread;
	struct proc *p = td->td_proc;
	char msg_buf[256];
	char key_buf[32];

	counter_u64_add(kernel_flags_captured, 1);

	if (key == 0xfe77c0de) {
		counter_u64_add(kernel_flags_captured_key, 1);
		strlcpy(key_buf, "correct", sizeof(key_buf));
	} else {
		snprintf(key_buf, sizeof(key_buf), "incorrect (0x%x)",
		    key);
	}

	/*
	 * Try to obtain the string and avoid faults where possible.
	 */
	if (message == NULL)
		strlcpy(msg_buf, "<null>", sizeof(msg_buf));
#ifdef __CHERI_PURE_CAPABILITY__
	else if (!cheri_gettag(message))
		snprintf(msg_buf, sizeof(msg_buf), "<untagged> %#p", message);
#endif
	else
		strlcpy(msg_buf, message, sizeof(msg_buf));

	log(LOG_ALERT,
	    "pid %d (%s), ABI: %s, jid %d, uid %d: message: (%s) key: %s\n",
	    p->p_pid, p->p_comm, p->p_sysent->sv_name,
	    p->p_ucred->cr_prison->pr_id, td->td_ucred->cr_uid,
	    msg_buf, key_buf);
}
