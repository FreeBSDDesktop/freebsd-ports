# $FreeBSD$

PORTNAME=	libevdev
PORTVERSION=	1.4.4
PORTREVISION=	2
CATEGORIES=	devel
MASTER_SITES=	http://freedesktop.org/software/${PORTNAME}/

MAINTAINER=	hselasky@FreeBSD.org
COMMENT=	Linux Event Device library

LICENSE=	MIT # without linux/*.h
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	${LOCALBASE}/include/linux/input.h:devel/evdev-proto

USES=		gmake libtool pathfix python:build tar:xz
EXTRACT_AFTER_ARGS=	--exclude include # evdev-proto
GNU_CONFIGURE=	yes
CONFIGURE_ENV=	ac_cv_path_DOXYGEN=""
CPPFLAGS+=	-I${LOCALBASE}/include # evdev-proto
INSTALL_TARGET=	install-strip
USE_LDCONFIG=	yes

post-patch:
	@${REINPLACE_CMD} -e '/input\.h/s,top_srcdir,LOCALBASE,' \
		${WRKSRC}/libevdev/Makefile.in
# XXX tools require signalfd(2), test require /dev/uinput
	@${REINPLACE_CMD} -e '/^SUBDIRS/s,tools test,,' \
		${WRKSRC}/Makefile.in

.include <bsd.port.mk>
