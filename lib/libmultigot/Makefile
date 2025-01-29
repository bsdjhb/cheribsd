.PATH: ${SRCTOP}/sys/libkern

SHLIB=	multigot
PACKAGE=clibs

INCS=	libmultigot.h

SRCS=	gsb_crc32.c
SRCS+=	one.c oneb.c
SRCS+=	two.c

COMPARTMENT_POLICY=	${.CURDIR}/compartments.json

.include <bsd.lib.mk>

CWARNFLAGS.gsb_crc32.c=	-Wno-cast-align
