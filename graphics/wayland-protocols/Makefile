# $FreeBSD$

PORTNAME=	wayland-protocols
PORTVERSION=	1.3
CATEGORIES=	graphics
MASTER_SITES=	https://wayland.freedesktop.org/releases/

MAINTAINER=	kwm@FreeBSD.org
COMMENT=	Wayland protocols

BUILD_DEPENDS=	wayland-scanner:graphics/wayland

USES=		tar:xz
GNU_CONFIGURE=	yes

post-patch:
	@${REINPLACE_CMD} -e 's|$${datadir}/pkgconfig|$${prefix}/libdata/pkgconfig|g' \
		${WRKSRC}/configure

.include <bsd.port.mk>
