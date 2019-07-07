--- shared/file-util.c.orig	2019-06-24 15:46:26 UTC
+++ shared/file-util.c
@@ -35,6 +35,8 @@
 
 #include "file-util.h"
 
+#define ETIME ETIMEDOUT
+
 static int
 current_time_str(char *str, size_t len, const char *fmt)
 {
