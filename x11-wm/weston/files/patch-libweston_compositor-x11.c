--- libweston/compositor-x11.c.orig	2017-08-08 18:57:03 UTC
+++ libweston/compositor-x11.c
@@ -37,6 +37,7 @@
 #include <errno.h>
 #include <sys/time.h>
 #include <sys/shm.h>
+#include <sys/stat.h>
 #include <linux/input.h>
 
 #include <xcb/xcb.h>
