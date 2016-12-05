# $FreeBSD$

PORTNAME=	libinput
PORTVERSION=	1.18.0
CATEGORIES=	x11

MAINTAINER=	x11@FreeBSD.org
COMMENT=	Generic input library

BUILD_DEPENDS=	v4l_compat>=0:${PORTSDIR}/multimedia/v4l_compat
LIB_DEPENDS=	libevdev.so:${PORTSDIR}/devel/libevdev

USE_GITHUB=	yes
GH_ACCOUNT=	kwm81
GH_TAGNAME=	778d6f2

USES=		autoreconf gmake libtool pathfix pkgconfig
GNU_CONFIGURE=	yes
PATHFIX_MAKEFILEIN?=	Makefile.am
CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
INSTALL_TARGET=	install-strip

.include <bsd.port.mk>
