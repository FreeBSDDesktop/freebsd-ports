# $FreeBSD$

PORTNAME=	xorgproto
PORTVERSION=	2018.4
CATEGORIES=	x11

MAINTAINER=	x11@FreeBSD.org
COMMENT=	xorg protocol headers

OPTIONS_DEFINE=	LEGACY
OPTIONS_DEFAULT=LEGACY
LEGACY_DESC=	Install legacy protocol headers

XORG_CAT=	proto

CONFIGURE_ARGS= --without-fop \
		--without-xmlto \
		--without-xsltproc

LEGACY_CONFIGURE_ENABLE=	legacy

.include <bsd.port.mk>
