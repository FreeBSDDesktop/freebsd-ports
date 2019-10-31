# Created by: Eric Anholt <anholt@FreeBSD.org>
# $FreeBSD$

PORTNAME=	libGLU
PORTVERSION=	9.0.1
CATEGORIES=	graphics
MASTER_SITES=	ftp://ftp.freedesktop.org/pub/mesa/glu/ \
		https://mesa.freedesktop.org/archive/glu/
DISTNAME=	glu-${PORTVERSION}

MAINTAINER=	x11@FreeBSD.org
COMMENT=	OpenGL utility library

LICENSE=       SGIB2
LICENSE_NAME=  SGI Free Software License B v2.0
LICENSE_FILE=  ${WRKSRC}/LICENSE
LICENSE_PERMS= auto-accept dist-mirror dist-sell pkg-mirror

USES=		gl libtool pathfix pkgconfig tar:xz xorg
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--disable-static
INSTALL_TARGET=	install-strip
USE_GL=		gl
USE_LDCONFIG=	yes

post-extract:
	@${HEAD} -29 ${WRKSRC}/include/GL/glu.h | \
		${CUT} -c 4- > ${WRKSRC}/LICENSE

.include <bsd.port.mk>
