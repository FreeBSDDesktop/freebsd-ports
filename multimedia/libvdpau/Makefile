# $FreeBSD$

PORTNAME=	libvdpau
PORTVERSION=	1.3
CATEGORIES=	multimedia

MAINTAINER=	madpilot@FreeBSD.org
COMMENT=	VDPAU wrapper and tracing library

USE_GITLAB=	yes
GL_SITE=	https://gitlab.freedesktop.org
GL_ACCOUNT=	vdpau
GL_PROJECT=	${PORTNAME:tl}
GL_COMMIT=	f57a9904c43ef5d726320c77baa91d0c38361ed4

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		libtool meson pkgconfig xorg
MESON_ARGS=	-Ddocumentation=false
USE_XORG=	x11 xext xorgproto
USE_LDCONFIG=	yes

post-patch:	.SILENT
	cd ${WRKSRC}/src && ${MV} vdpau_wrapper.cfg vdpau_wrapper.cfg.sample
	${REINPLACE_CMD} 's/vdpau_wrapper.cfg/&.sample/' \
		${WRKSRC}/src/meson.build

.include <bsd.port.mk>
