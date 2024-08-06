.PATH: ${SRCTOP}/sys/libkern

SHLIB=	multigot
PACKAGE=clibs

INCS=	libmultigot.h

COMPARTMENTS= crc32 one two

SRCS.crc32=	gsb_crc32.c
SRCS.one=	one.c oneb.c
SRCS.two=	two.c

.include <bsd.lib.mk>

CWARNFLAGS.gsb_crc32.c=	-Wno-cast-align
