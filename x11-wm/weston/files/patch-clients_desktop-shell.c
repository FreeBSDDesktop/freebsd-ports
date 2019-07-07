--- clients/desktop-shell.c.orig	2019-06-24 15:46:26 UTC
+++ clients/desktop-shell.c
@@ -39,6 +39,7 @@
 #include <ctype.h>
 #include <time.h>
 #include <assert.h>
+#include <signal.h>
 
 #include <wayland-client.h>
 #include "window.h"
@@ -48,6 +49,8 @@
 #include "shared/xalloc.h"
 #include "shared/zalloc.h"
 #include "shared/file-util.h"
+
+#define program_invocation_short_name getprogname()
 
 #include "weston-desktop-shell-client-protocol.h"
 
