--- libweston/input.c.orig	2017-08-08 18:57:03 UTC
+++ libweston/input.c
@@ -32,7 +32,8 @@
 #include <sys/mman.h>
 #include <assert.h>
 #include <unistd.h>
-#include <values.h>
+//#include <values.h>
+#include <float.h>
 #include <fcntl.h>
 #include <limits.h>
 
