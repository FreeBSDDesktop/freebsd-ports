# $FreeBSD$
# 
# xorg ports categories and internal stuff
#
# Feature:	xorg-cat
# Usage:	USES=xorg-cat:<category>
# 		<category> is one of:
#
# 		* app - Installs applications, no shared libraries.
# 		* data - Installs only data.
# 		* doc - no particular notes
# 		* driver - depends on xorgproto at least
# 		* font - don't install .pc file
# 		* lib - various dependencies, install .pc file, needs pathfix
# 		* proto - install .pc file, needs pathfix, most only needed at build time.
# 		* xserver - there's only one atm, I guess everything can fit into the port itself
#
#.MAINTAINER:	x11@FreeBSD.org

.if !defined(_INCLUDE_USES_XORG_CAT_MK)
_INCLUDE_USES_XORG_CAT_MK=yes

_XORG_CATEGORIES=	app data doc driver font lib proto util xserver
_XORG_BUILDSYSTEMS=	autotools meson

_XORG_CAT=		# empty
_XORG_BUILDSYS=		# empty

.if empty(xorg-cat_ARGS)
IGNORE=		no arguments specified to xorg_cat
.endif

.for _arg in ${xorg-cat_ARGS}
.  if ${_XORG_CATEGORIES:M${_arg}}
.    if empty(_XORG_CAT)
_XORG_CAT=	${_arg}
.    else
IGNORE=		multipe xorg categories specified via xorg_cat:${xorg-cat_ARGS:S/ /,/gW}
.    endif
.  elif ${_XORG_BUILDSYSTEMS:M${_arg}}
.    if empty(_XORG_BUILDSYS)
_XORG_BUILDSYS=	${_arg}
.    else
IGNORE=		multipe xorg build systems specified via xorg_cat:${xorg-cat_ARGS:S/ /,/gW}
.    endif
.  else
IGNORE=		unknown argument specified via xorg_cat:${xorg-cat_ARGS:S/ /,/gW}
.  endif
.endfor

# Default to the autotools build system
.if empty(_XORG_BUILDSYS)
_XORG_BUILDSYS=		autotools
.endif

# Default variables, common to all new modular xorg ports.
.if empty(USES:Mtar)
EXTRACT_SUFX?=		.tar.bz2
.endif

DIST_SUBDIR=	xorg/${_XORG_CAT}

.if ${_XORG_BUILDSYS} == "meson"
.include "${USESDIR}/meson.mk"
.elif ${_XORG_BUILDSYS} == "autotools"
GNU_CONFIGURE=		yes
.else
# This should not happen
IGNORE=		unknown build system specified via xorg_cat:${xorg-cat_ARGS:S/ /,/gW}
.endif

.if defined(USE_GITLAB)
# this needs more work
GL_SITE?=		https://gitlab.freedesktop.org
GL_ACCOUNT?=		xorg
.else
MASTER_SITES?=		${MASTER_SITE_XORG}
MASTER_SITE_SUBDIR?=	individual/${_XORG_CAT}
.endif

# set up things for includes below
libtool_ARGS?=	# empty

#
## All xorg ports needs pkgconfig to build, but some ports look for pkgconfig and
## then continues the build.
.include "${USESDIR}/pkgconfig.mk"

#
## All xorg ports needs xorg-macros.
.if ${PORTNAME} != xorg-macros
USE_XORG+=      xorg-macros
.endif

.if ${_XORG_CAT} == "app"
# Nothing at the moment
.endif

.if ${_XORG_CAT} == "data"
# Nothing at the moment.
.endif

.if ${_XORG_CAT} == "driver"
USE_XORG+=	xi xorg-server xorgproto
.  if ${_XORG_BUILDSYS} == "meson"
# Put special stuff for meson here
.  else
CONFIGURE_ENV+=	DRIVER_MAN_SUFFIX=4x DRIVER_MAN_DIR='$$(mandir)/man4'
.include "${USESDIR}/libtool.mk"
INSTALL_TARGET=	install-strip
.  endif
.endif

.if ${_XORG_CAT} == "font"
FONTNAME?=	${PORTNAME:C/.*-//g:S/type/Type/:S/ttf/TTF/:S/speedo/Speedo/}
.  if ${_XORG_BUILDSYS} == "meson"
# Put special stuff for meson here
.  else
CONFIGURE_ARGS+=	--with-fontrootdir=${PREFIX}/share/fonts
CONFIGURE_ENV+=	FONTROOTDIR=${PREFIX}/share/fonts
.  endif
.  if !defined(NOFONT)
.include "${USESDIR}/fonts.mk"
BUILD_DEPENDS+=	mkfontscale>=0:x11-fonts/mkfontscale \
		bdftopcf:x11-fonts/bdftopcf
PLIST_FILES+=	"@comment ${FONTSDIR}/fonts.dir" \
		"@comment ${FONTSDIR}/fonts.scale"
.  endif
.endif

.if ${_XORG_CAT} == "lib"
.include "${USESDIR}/pathfix.mk"
.  if ${_XORG_BUILDSYS} == "meson"
# put meson stuff here
.  else
.include "${USESDIR}/libtool.mk"
USE_LDCONFIG=	yes
CONFIGURE_ARGS+=--enable-malloc0returnsnull
.  endif
.endif

.if ${_XORG_CAT} == "proto"
.include "${USESDIR}/pathfix.mk"
.endif

.if ${_XORG_CAT} == "xserver"
DISTFILES?=	xorg-server-${PORTVERSION}.tar.bz2
WRKSRC=		${WRKDIR}/xorg-server-${PORTVERSION}
.include "${USESDIR}/pathfix.mk"
.  if ${_XORG_BUILDSYS} == "meson"
# put meson stuff here
.  else
CONFIGURE_ARGS+=	--with-xkb-path=${LOCALBASE}/share/X11/xkb \
			--with-fontrootdir=${LOCALBASE}/share/fonts
.  endif
LIB_PC_DEPENDS+=	${LOCALBASE}/libdata/pkgconfig/dri.pc:graphics/mesa-dri
USE_XORG+=	fontutil:build
.endif

.include "${USESDIR}/xorg.mk"

.endif
