# Created by: kwm@FreeBSD.org
# $FreeBSD$

PORTNAME=	wayland
PORTVERSION=	1.10.0
CATEGORIES=	graphics
MASTER_SITES=	http://rainbow-runner.nl/freebsd/
#http://wayland.freedesktop.org/releases/

MAINTAINER=	x11@FreeBSD.org
COMMENT=	Wayland composite "server"

LIB_DEPENDS=	libexpat.so:textproc/expat2 \
		libffi.so:devel/libffi

WITH_DEBUG=	1
USES=		gmake libtool pathfix pkgconfig tar:xz
USE_GNOME=	libxslt:build
USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--disable-documentation
INSTALL_TARGET=	install-strip

CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib

.include <bsd.port.mk>
