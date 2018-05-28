# $FreeBSD$

PORTNAME=	libglvnd
PORTVERSION=	20180524
CATEGORIES=	graphics

MAINTAINER=	x11@FreeBSD.org
COMMENT=	GL vendor-neutral dispatch library

LICENSE=	NVIDIA
LICENSE_NAME=	License For Customer Use of NVIDIA Software
LICENSE_FILE=	${WRKSRC}/README.md
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

USES=		autoreconf libtool tar:xz
USE_XORG=	x11 xext

USE_GITHUB=	yes
GH_TUPLE=	NVIDIA:libglvnd:8709003ffdc905d144855c3117a31da220149d4c

GNU_CONFIGURE=	yes
INSTALL_TARGET=	install-strip

.include <bsd.port.mk>
