--- configure.ac.orig	2016-06-21 14:31:09.000000000 +0200
+++ configure.ac	2016-07-08 13:05:53.236433000 +0200
@@ -79,6 +79,7 @@
 DRI3PROTO_REQUIRED=1.0
 PRESENTPROTO_REQUIRED=1.0
 LIBUDEV_REQUIRED=151
+LIBDEVQ_REQUIRED=0.0.2
 GLPROTO_REQUIRED=1.4.14
 LIBOMXIL_BELLAGIO_REQUIRED=0.0
 LIBVA_REQUIRED=0.38.0
@@ -871,7 +872,7 @@
     [enable_dri=yes])
 
 case "$host_os" in
-linux*)
+linux*|freebsd*)
     dri3_default=yes
     ;;
 *)
@@ -1311,6 +1312,9 @@
 PKG_CHECK_MODULES([LIBUDEV], [libudev >= $LIBUDEV_REQUIRED],
                   have_libudev=yes, have_libudev=no)
 
+PKG_CHECK_MODULES([LIBDEVQ], [libdevq-1.0 >= $LIBDEVQ_REQUIRED],
+                  have_libdevq=yes, have_libdevq=no)
+
 AC_ARG_ENABLE([sysfs],
     [AS_HELP_STRING([--enable-sysfs],
         [enable /sys PCI identification @<:@default=disabled@:>@])],
@@ -1408,6 +1412,10 @@
     DEFINES="$DEFINES -DHAVE_LIBUDEV"
     have_pci_id=yes
 fi
+if test "$have_libdevq" = yes; then
+    DEFINES="$DEFINES -DHAVE_LIBDEVQ"
+    have_pci_id=yes
+fi
 
 if test "$have_sysfs" = yes; then
     DEFINES="$DEFINES -DHAVE_SYSFS"
@@ -1540,6 +1548,23 @@
         ;;
     gnu*)
         DEFINES="$DEFINES -DHAVE_ALIAS"
+dnl not sure about dri3 support, just enable it for now.
+        if test "x$enable_dri3" = xyes; then
+            DEFINES="$DEFINES -DHAVE_DRI3"
+        fi
+
+        if test "x$have_libdevq" != xyes; then
+            AC_MSG_ERROR([libdevq required for building DRI])
+        fi
+
+        case "$host_cpu" in
+        powerpc* | sparc*)
+            # Build only the drivers for cards that exist on PowerPC/sparc
+            if test "x$with_dri_drivers" = "xyes"; then
+                with_dri_drivers="r200 radeon swrast"
+            fi
+            ;;
+        esac
         ;;
     cygwin*)
         if test "x$with_dri_drivers" = "xyes"; then
@@ -1746,6 +1771,8 @@
 AM_CONDITIONAL(HAVE_GBM, test "x$enable_gbm" = xyes)
 if test "x$need_pci_id$have_libudev" = xyesyes; then
     GBM_PC_REQ_PRIV="libudev >= $LIBUDEV_REQUIRED"
+elif test "x$need_libdevq" = xyes; then
+    GBM_PC_REQ_PRIV="libdevq-1.0 >= $LIBDEVQ_REQUIRED"
 else
     GBM_PC_REQ_PRIV=""
 fi
@@ -1921,9 +1948,19 @@
         AC_MSG_ERROR([cannot enable OpenCL without Gallium])
     fi
 
+    if test "x$acv_mesa_CLANG" = xno; then
+
+    GCC_VERSION=`$CC -dumpversion`
+    if test $? -eq 0; then
+        GCC_VERSION_MAJOR=`echo $GCC_VERSION | cut -d. -f1`
+        GCC_VERSION_MINOR=`echo $GCC_VERSION | cut -d. -f2`
+    fi
+
     if test $GCC_VERSION_MAJOR -lt 4 -o $GCC_VERSION_MAJOR -eq 4 -a $GCC_VERSION_MINOR -lt 7; then
         AC_MSG_ERROR([gcc >= 4.7 is required to build clover])
     fi
+# end of clang test.
+    fi
 
     if test "x$have_libclc" = xno; then
         AC_MSG_ERROR([pkg-config cannot find libclc.pc which is required to build clover.
@@ -2102,9 +2139,9 @@
 strip_unwanted_llvm_flags() {
     # Use \> (marks the end of the word)
     echo `$1` | sed \
-	-e 's/-march=\S*//g' \
-	-e 's/-mtune=\S*//g' \
-	-e 's/-mcpu=\S*//g' \
+	-e 's/-march=[[:graph:]]* //g' \
+	-e 's/-mtune=[[:graph:]]* //g' \
+	-e 's/-mcpu=[[:graph:]]* //g' \
 	-e 's/-DNDEBUG\>//g' \
 	-e 's/-D_GNU_SOURCE\>//g' \
 	-e 's/-pedantic\>//g' \
@@ -2196,8 +2233,6 @@
                 CLANG_LIBDIR=${LLVM_LIBDIR}
             fi
             CLANG_RESOURCE_DIR=$CLANG_LIBDIR/clang/${LLVM_VERSION}
-            AS_IF([test ! -f "$CLANG_RESOURCE_DIR/include/stddef.h"],
-                [AC_MSG_ERROR([Could not find clang internal header stddef.h in $CLANG_RESOURCE_DIR Use --with-clang-libdir to specify the correct path to the clang libraries.])])
         fi
     else
         MESA_LLVM=0
