--- libweston/input.c.orig	2019-06-24 15:46:26 UTC
+++ libweston/input.c
@@ -34,7 +34,8 @@
 #include <sys/mman.h>
 #include <assert.h>
 #include <unistd.h>
-#include <values.h>
+//#include <values.h>
+#include <float.h>
 #include <fcntl.h>
 #include <limits.h>
 #include <errno.h>
