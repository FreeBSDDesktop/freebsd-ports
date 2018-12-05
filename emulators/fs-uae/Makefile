# Created by: Danilo Egea Gondolfo <danilo@FreeBSD.org>
# $FreeBSD$

PORTNAME=	fs-uae
PORTVERSION=	2.8.4
PORTREVISION=	5
CATEGORIES=	emulators
MASTER_SITES=	http://fs-uae.net/stable/${PORTVERSION}/

MAINTAINER=	tomse@oagd.net
COMMENT=	Amiga emulator

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libpng.so:graphics/png \
		libopenal.so:audio/openal-soft \
		libmpeg2.so:multimedia/libmpeg2

USES=		gettext gmake pkgconfig gnome gl desktop-file-utils shared-mime-info
USE_XORG=	x11
USE_SDL=	sdl2
USE_GL=		gl
USE_GNOME=	glib20
LLD_UNSAFE=	yes
INSTALLS_ICONS=	yes
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--disable-jit
CFLAGS=		-Wno-c++11-narrowing -I/usr/local/include

OPTIONS_DEFINE=	DOCS

post-stage:
	@cp -R ${WRKSRC}/share/fs-uae ${STAGEDIR}${PREFIX}/share/

.include <bsd.port.mk>
