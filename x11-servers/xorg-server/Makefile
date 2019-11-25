# Created by: Eric Anholt <anholt@FreeBSD.org>
# $FreeBSD$

PORTNAME?=	xorg-server
PORTVERSION?=	1.20.5
PORTREVISION?=	0
PORTEPOCH?=	1
CATEGORIES=	x11-servers
MASTER_SITES=	XORG/individual/xserver
DISTNAME=	xorg-server-${PORTVERSION}

MAINTAINER=	x11@FreeBSD.org
COMMENT?=	X.Org X server and related programs

LICENSE=	MIT

RUN_DEPENDS+=	xkeyboard-config>=2.5:x11/xkeyboard-config \
		xkbcomp:x11/xkbcomp

SLAVE_PORT?=	no

OPTIONS_SUB=	yes
OPTIONS_DEFINE=	SUID
OPTIONS_RADIO=	CONF
OPTIONS_RADIO_CONF=	DEVD HAL UDEV
OPTIONS_DEFAULT=	DEVD SUID

SUID_DESC=	Install setuid wrapper to allow startx as non-root
CONF_DESC=	Backend to use for input device configuration
DEVD_DESC=	Use devd (native)
HAL_DESC=	Use HAL (deprecated)
UDEV_DESC=	Use udev via libudev-devd (experimental)

OPTIONS_EXCLUDE_sparc64=	HAL

DEVD_CONFIGURE_ENABLE=	config-devd
HAL_CONFIGURE_ENABLE=	config-hal
HAL_LIB_DEPENDS=	libhal.so:sysutils/hal \
			libdbus-1.so:devel/dbus
SUID_CONFIGURE_ENABLE=	suid-wrapper
SUID_CONFIGURE_ON=	--libexecdir=${PREFIX}/bin	# set SUID_WRAPPER_DIR
UDEV_CONFIGURE_ENABLE=	config-udev
UDEV_CONFIGURE_ON=	--disable-config-udev-kms
UDEV_LIB_DEPENDS=	libudev.so:devel/libudev-devd

USES=		gmake gl libtool perl5 ssl tar:bzip2 xorg xorg-cat:xserver
USE_PERL5=	build
USE_GL+=	gl
USE_XORG+=	pixman xau xdmcp xfont2 xkbfile xorgproto xshmfence xtrans
CONFIGURE_ARGS+=--without-doxygen --without-xmlto --without-fop \
		--without-dtrace --with-shared-memory-dir=/tmp \
		--disable-install-setuid
INSTALL_TARGET=	install-strip

.if ${SLAVE_PORT} == "no" || ${PORTNAME} == "xephyr" || ${PORTNAME} == "xwayland"
LIB_DEPENDS+=	libdrm.so:graphics/libdrm \
		libepoxy.so:graphics/libepoxy
.else
BUILD_DEPENDS+=	libepoxy>0:graphics/libepoxy	# only for configure
.endif

.if ${SLAVE_PORT} == "no"
USE_GL+=	gbm
USE_XORG+=	pciaccess
CONFIGURE_ARGS+=--disable-dmx --disable-xephyr --disable-xnest --disable-xvfb \
		--disable-xwayland --enable-xcsecurity
SUB_FILES=	pkg-install pkg-deinstall
.else
CONFIGURE_ARGS+=	--disable-xorg
OPTIONS_EXCLUDE=	DEVD HAL UDEV SUID
# Set PLIST for slave ports so they only need to set PLIST_FILES
PLIST=		${.CURDIR}/pkg-plist
.endif

.include <bsd.port.pre.mk>

.if ${SSL_DEFAULT} == base
# The reason why I use this is cause openssl from base doesn't install a .pc file
# and configure will fail trying to find it. Setting both of those variables to
# a *non-empty* value by-passes the pkg-config check.
CONFIGURE_ENV=	SHA1_LIB="-L/usr/lib -lcrypto" SHA1_CFLAGS="-I/usr/include"
.endif

.if ${ARCH} == "i386" || ${ARCH} == "amd64"
LIB_DEPENDS+=	libunwind.so:devel/libunwind
.endif

.if ${ARCH} == "sparc64"
PLIST_SUB+=	SPARC64=""
.else
PLIST_SUB+=	SPARC64="@comment "
.endif

post-patch:
	@${REINPLACE_CMD} 's/test.*-traditional.*;/true;/' \
		${WRKSRC}/configure

.if ${SLAVE_PORT} == "no"
post-install:
# Avoid conflict with nvidia-driver, move libglx.so into .xorg directory
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/xorg/modules/extensions/.xorg
	${MV} ${STAGEDIR}${PREFIX}/lib/xorg/modules/extensions/libglx.so \
		${STAGEDIR}${PREFIX}/lib/xorg/modules/extensions/.xorg/
	@${MKDIR} ${STAGEDIR}${PREFIX}/etc/X11/xorg.conf.d
.endif # ! SLAVE_PORT

.include <bsd.port.post.mk>
