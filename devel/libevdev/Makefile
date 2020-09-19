# $FreeBSD$

PORTNAME=	libevdev
PORTVERSION=	1.9.1.20200919
CATEGORIES=	devel
#MASTER_SITES=	http://freedesktop.org/software/${PORTNAME}/

MAINTAINER=	hselasky@FreeBSD.org
COMMENT=	Linux Event Device library

PATCH_SITES=	https://gitlab.freedesktop.org/${PORTNAME}/${PORTNAME}/-/commit/
PATCHFILES+=	6ea230bc72353c54fac628987b87cc1d3b6fd842.diff:-p1 # https://gitlab.freedesktop.org/libevdev/libevdev/-/merge_requests/70

LICENSE=	MIT # without linux/*.h
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		meson pkgconfig python:3.5+,build shebangfix
USE_LDCONFIG=	yes

USE_GITLAB=	yes
GL_SITE=	https://gitlab.freedesktop.org
GL_COMMIT=	44b5c9bd9fc3694124ce1af815656bbda3ce6329

MESON_ARGS=	-Ddocumentation=disabled -Dtests=disabled

BINARY_ALIAS=	python3=${PYTHON_CMD}


.include <bsd.port.mk>
