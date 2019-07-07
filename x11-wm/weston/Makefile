# Created by: Johannes Lundberg <johalun0@gmail.com>
# $FreeBSD$

PORTNAME=	weston
PORTVERSION=	3.0.0
CATEGORIES=	x11-wm wayland
MASTER_SITES=	http://wayland.freedesktop.org/releases/

MAINTAINER=	johalun0@gmail.com
COMMENT=	Wayland Reference Compositor

LICENSE=	MIT

BUILD_DEPENDS=	wayland-protocols>=1.7:graphics/wayland-protocols
LIB_DEPENDS=	libxkbcommon.so:x11/libxkbcommon \
		libpixman-1.so:x11/pixman \
		libcairo.so:graphics/cairo \
		libpango-1.0.so:x11-toolkits/pango \
		libcolord.so:graphics/colord \
		libfontconfig.so:x11-fonts/fontconfig \
		libfreetype.so:print/freetype2 \
		libwayland-server.so:graphics/wayland \
		libevent.so:devel/libevent \
		libpng.so:graphics/png \
		libwebp.so:graphics/webp \
		libffi.so:devel/libffi \
		libepoll-shim.so:devel/libepoll-shim \
		libudev.so:devel/libudev-devd \
		libunwind.so:devel/libunwind \
		libevdev.so:devel/libevdev \
		libinput.so:x11/libinput \
		libmtdev.so:devel/libmtdev \
		liblcms2.so:graphics/lcms2

USES=	autoreconf alias gmake pathfix jpeg libtool pkgconfig tar:xz \
	localbase:ldflags

USE_XORG=	x11 xcb xcursor
USE_GL=		egl gbm glesv2
USE_LDCONFIG=	yes

OPTIONS_SUB=	yes
OPTIONS_DEFINE=	SUID CLIENTS CLIENTS_INSTALL XWAYLAND
OPTIONS_MULTI=	COMPOSITORS
OPTIONS_MULTI_COMPOSITORS=	X11 DRM WAYLAND SCFB
OPTIONS_SINGLE=	CAIRO
OPTIONS_SINGLE_CAIRO=	CAIROIMAGE CAIROGL CAIROGLESV2

OPTIONS_DEFAULT=	SUID CAIROIMAGE CLIENTS CLIENTS_INSTALL XWAYLAND X11 DRM WAYLAND SCFB

CAIRO_DESC=		Cairo backend
CAIROGL_DESC=		GL (enabled in cairo by default)
CAIROGLESV2_DESC=	GLESv2 (requires cairo built with --enable-glesv2)
CAIROIMAGE_DESC=	Image (Recommended)
CLIENTS_DESC=		Build Weston clients
CLIENTS_INSTALL_DESC=	Install Weston clients
DRM_DESC=		Hardware accelerated compositor backend
SCFB_DESC=		Software rendered compositor backend
SUID_DESC=		Install weston-launch binary with setuid bit set
WAYLAND_DESC=		Nested Weston compositors
X11_DESC=		Run Weston as X11 client (good for testing)
XWAYLAND_DESC=		Support running X clients in Weston

CAIROIMAGE_CONFIGURE_ON=	--with-cairo=image
CAIROGL_CONFIGURE_ON=		--with-cairo=gl
CAIROGLESV2_CONFIGURE_ON=	--with-cairo=glesv2 --with-cairo-glesv2
CLIENTS_CONFIGURE_ENABLE=	clients
CLIENTS_INSTALL_CONFIGURE_ENABLE=	demo-clients-install
DRM_CONFIGURE_ENABLE=		drm-compositor
DRM_LIB_DEPENDS=		libdrm.so:graphics/libdrm
SCFB_CONFIGURE_ENABLE=		scfb-compositor
WAYLAND_CONFIGURE_ENABLE=	wayland-compositor
X11_CONFIGURE_ENABLE=		x11-compositor
XWAYLAND_CONFIGURE_ENABLE=	xwayland

CPPFLAGS+=	-I${LOCALBASE}/include/libepoll-shim

GROUPS=		weston-launch

GNU_CONFIGURE=	YES

CONFIGURE_ARGS=		--enable-weston-launch
CONFIGURE_ARGS+=	--disable-fbdev-compositor
CONFIGURE_ARGS+=	--disable-vaapi-recorder
#CONFIGURE_ARGS+=	--disable-xwayland-test

# We handle setuid in the plist. This allows to build as a user.
CONFIGURE_ARGS+=	--disable-setuid-install

CONFIGURE_ENV+=	LIBS="-lepoll-shim -lrt -lEGL"
CONFIGURE_ENV+=	EGL_TESTS_LIBS="-lwayland-client -lGLESv2 -lwayland-egl -lwayland-client"
CONFIGURE_ENV+=	EGL_TESTS_CFLAGS="-L${STAGEDIR}${PREFIX}/lib -I${STAGEDIR}${PREFIX}/include"

INSTALL_TARGET=	install-strip

.include <bsd.port.options.mk>

.if !empty(PORT_OPTIONS:MCLIENTS_INSTALL)
USE_GNOME+=glib20
.endif

# Should not have to do this. "make" should find them in $WAYLAND_PROTOCOLS_DATADIR set by automake...
WAYLAND_PROTOCOLS_DATADIR=`pkg-config --variable=pkgdatadir wayland-protocols`
pre-configure:
	@${CP} ${WAYLAND_PROTOCOLS_DATADIR}/stable/*/* ${WRKSRC}/protocol/
	@${CP} ${WAYLAND_PROTOCOLS_DATADIR}/unstable/*/* ${WRKSRC}/protocol/
	@if ! pkg-config --exists wayland-egl; then \
		${ECHO_MSG} "${PKGNAME}: Needs mesa-libs with wayland support enabled."; \
		${FALSE}; \
	fi

.include <bsd.port.mk>
