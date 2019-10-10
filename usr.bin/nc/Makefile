# $FreeBSD$

.include <src.opts.mk>

.PATH: ${SRCTOP}/contrib/netcat

PROG=	nc
SRCS=	netcat.c atomicio.c socks.c

CFLAGS+=-DIPSEC
LIBADD=	ipsec

.if ${MK_STATS} != "no" && !defined(RESCUE)
LIBADD+=	sbuf stats
CFLAGS+=	-DWITH_STATS
.endif

WARNS?=	2
LD_FATAL_WARNINGS=no

.include <bsd.prog.mk>
