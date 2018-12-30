# Created by: johalun0@gmail.com
# $FreeBSD$

PORTNAME=	libwacom
PORTVERSION=	0.32
DISTVERSIONPREFIX=libwacom-
CATEGORIES=	x11

MAINTAINER=	x11@FreeBSD.org
COMMENT=	Adds tablet support to libinput

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	${LOCALBASE}/include/linux/input.h:devel/evdev-proto
LIB_DEPENDS=	libgudev-1.0.so:devel/libgudev

USE_GITHUB=	yes
GH_ACCOUNT=	linuxwacom

USES=		autoreconf gettext-runtime gmake gnome libtool localbase \
		pkgconfig pathfix tar:bzip2
USE_GNOME=	glib20
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes
INSTALL_TARGET=	install-strip

OPTIONS_DEFINE=	LAYOUT_GUI
OPTIONS_SUB=	yes

LAYOUT_GUI_DESC=Build the layout image viewer

LAYOUT_GUI_USE=	GNOME=gtk20,librsvg2

post-patch:
	@${REINPLACE_CMD} -e 's/-printf "%P\\n"/-print0 | xargs -0 basename/' ${WRKSRC}/data/Makefile.am

.include <bsd.port.mk>
