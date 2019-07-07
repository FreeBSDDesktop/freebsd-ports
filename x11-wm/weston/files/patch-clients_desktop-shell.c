--- clients/desktop-shell.c.orig	2017-08-08 18:57:02 UTC
+++ clients/desktop-shell.c
@@ -41,6 +41,7 @@
 #include <ctype.h>
 #include <time.h>
 #include <assert.h>
+#include <signal.h>
 
 #include <wayland-client.h>
 #include "window.h"
@@ -49,6 +50,8 @@
 #include "shared/helpers.h"
 #include "shared/xalloc.h"
 #include "shared/zalloc.h"
+
+#define program_invocation_short_name getprogname()
 
 #include "weston-desktop-shell-client-protocol.h"
 
