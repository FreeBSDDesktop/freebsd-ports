--- libweston/pixel-formats.c.orig	2017-08-08 18:57:03 UTC
+++ libweston/pixel-formats.c
@@ -25,7 +25,7 @@
 
 #include "config.h"
 
-#include <endian.h>
+#include <sys/endian.h>
 #include <inttypes.h>
 #include <stdbool.h>
 #include <unistd.h>
