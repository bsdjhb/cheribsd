/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2008 Isilon Inc http://www.isilon.com/
 * Authors: Doug Rabson <dfr@rabson.org>
 * Developed with Red Inc: Alfred Perlstein <alfred@freebsd.org>
 *
 * Copyright (c) 2014-2015 The FreeBSD Foundation.
 *
 * Portions of this software were developed by Konstantin Belousov
 * under sponsorship from the FreeBSD Foundation.
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
/*
 * CHERI CHANGES START
 * {
 *   "updated": 20221129,
 *   "target_type": "lib",
 *   "changes": [
 *     "calling_convention"
 *   ]
 * }
 * CHERI CHANGES END
 */

#include <fcntl.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "libc_private.h"

#pragma weak fcntl
int
fcntl(int fd, int cmd, ...)
{
	va_list args;
	intptr_t arg;

	va_start(args, cmd);
	switch (cmd) {
	case F_GETLK:
	case F_SETLK:
	case F_SETLKW:
	case F_KINFO:
		arg = va_arg(args, intptr_t);
		break;

	case F_GETFD:
	case F_GETFL:
	case F_GETOWN:
	case F_GET_SEALS:
	case F_ISUNIONSTACK:
		arg = 0;
		break;

	default:
		arg = va_arg(args, int);
		break;
	}
	va_end(args);

	return (INTERPOS_SYS(fcntl, fd, cmd, arg));
}

#ifdef __CHERI_PURE_CAPABILITY__
int _fcntl(int fd, int cmd, ...);
#pragma weak _fcntl
int
_fcntl(int fd, int cmd, ...)
{
	va_list args;
	intptr_t arg;

	va_start(args, cmd);
	switch (cmd) {
	case F_GETLK:
	case F_SETLK:
	case F_SETLKW:
	case F_KINFO:
		arg = va_arg(args, intptr_t);
		break;

	case F_GETFD:
	case F_GETFL:
	case F_GETOWN:
	case F_GET_SEALS:
	case F_ISUNIONSTACK:
		arg = 0;
		break;

	default:
		arg = va_arg(args, int);
		break;
	}
	va_end(args);

	return (__sys_fcntl(fd, cmd, arg));
}
#endif
