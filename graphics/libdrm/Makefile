# Created by: lesi@FreeBSD.org
# $FreeBSD$

PORTNAME=	libdrm
PORTVERSION=	2.4.101
PORTEPOCH=	1
CATEGORIES=	graphics x11

MAINTAINER=	x11@FreeBSD.org
COMMENT=	Userspace interface to kernel Direct Rendering Module services

LICENSE=	MIT

BUILD_DEPENDS=	${LOCALBASE}/libdata/pkgconfig/pthread-stubs.pc:devel/libpthread-stubs
LIB_DEPENDS=	libpciaccess.so:devel/libpciaccess

USES=		gnome meson pkgconfig
USE_GITLAB=	yes
GL_SITE=	https://gitlab.freedesktop.org
GL_ACCOUNT=	mesa
GL_PROJECT=	drm
GL_COMMIT=	c997baf590de48ac5fc52a6e2df806e0a6f3acfc
USE_LDCONFIG=	yes

OPTIONS_DEFINE=	MANPAGES TESTS
OPTIONS_SUB=	yes

TESTS_DESC=	Install test programs (which are always built)

.if defined(PACKAGE_BUILDING)
OPTIONS_DEFAULT+=	MANPAGES
.endif

MANPAGES_BUILD_DEPENDS=	${LOCALBASE}/share/xsl/docbook/manpages/docbook.xsl:textproc/docbook-xsl
MANPAGES_USE=		GNOME=libxslt:build
MANPAGES_MESON_TRUE=	man-pages

TESTS_MESON_TRUE=	install-test-programs

# avoid circular dependency in case cairo supports OpenGL (cairo->mesa-libs->libdrm->cairo)
CONFIGURE_ARGS+=	-Dcairo-tests=false

.include <bsd.port.options.mk>

.if ${ARCH} == amd64 || ${ARCH} == i386
PLIST_SUB+=	ARM_DRIVERS="@comment "
PLIST_SUB+=	INTEL_DRIVER=""
PLIST_SUB+=	NOUVEAU_DRIVER=""
PLIST_SUB+=	RADEON_DRIVERS=""
.elif ${ARCH:Mpowerpc*}
PLIST_SUB+=	ARM_DRIVERS="@comment "
PLIST_SUB+=	INTEL_DRIVER="@comment "
PLIST_SUB+=	NOUVEAU_DRIVER=""
PLIST_SUB+=	RADEON_DRIVERS=""
.elif ${ARCH} == aarch64
PLIST_SUB+=	ARM_DRIVERS=""
PLIST_SUB+=	INTEL_DRIVER="@comment "
PLIST_SUB+=	NOUVEAU_DRIVER=""
PLIST_SUB+=	RADEON_DRIVERS=""
.elif ${ARCH:Marm*}
PLIST_SUB+=	ARM_DRIVERS=""
PLIST_SUB+=	INTEL_DRIVER="@comment "
PLIST_SUB+=	NOUVEAU_DRIVER="@comment "
PLIST_SUB+=	RADEON_DRIVERS="@comment "
.else
PLIST_SUB+=	ARM_DRIVERS="@comment "
PLIST_SUB+=	INTEL_DRIVER="@comment "
PLIST_SUB+=	NOUVEAU_DRIVER="@comment "
PLIST_SUB+=	RADEON_DRIVERS="@comment "
.endif

.include <bsd.port.mk>
