# Created by: gahr
# $FreeBSD$

PORTNAME=	libxatracker
PORTVERSION=	${MESAVERSION}
CATEGORIES=	graphics

COMMENT=	Mesa XA state tracker

USE_XORG=	xorgproto

.include <bsd.port.options.mk>
.include "${.CURDIR:H:H}/graphics/mesa-dri/Makefile.common"

CONFIGURE_ARGS+=	--disable-dri \
			--disable-egl \
			--disable-gbm \
			--disable-gles2 \
			--disable-glx \
			--disable-opengl \
			--disable-shared-glapi \
			--with-gallium-drivers= \
			--with-platforms=

MESA_BUILD_WRKSRC=	src/compiler src/util
LDFLAGS_i386=		-Wl,-znotext

CONFIGURE_ARGS+=	--enable-xa
MESA_BUILD_WRKSRC+=	src/gallium
MESA_INSTALL_WRKSRC=	src/gallium/state_trackers/xa src/gallium/targets/xa

.include "${MASTERDIR}/Makefile.targets"
.include <bsd.port.post.mk>
