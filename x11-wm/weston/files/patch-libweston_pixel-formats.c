--- libweston/pixel-formats.c.orig	2019-06-24 15:46:26 UTC
+++ libweston/pixel-formats.c
@@ -26,7 +26,7 @@
 
 #include "config.h"
 
-#include <endian.h>
+#include <sys/endian.h>
 #include <inttypes.h>
 #include <stdbool.h>
 #include <unistd.h>
