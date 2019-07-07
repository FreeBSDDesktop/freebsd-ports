--- shared/file-util.c.orig	2017-08-08 18:57:03 UTC
+++ shared/file-util.c
@@ -34,6 +34,8 @@
 
 #include "file-util.h"
 
+#define ETIME ETIMEDOUT
+
 static int
 current_time_str(char *str, size_t len, const char *fmt)
 {
