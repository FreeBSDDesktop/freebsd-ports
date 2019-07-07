--- tests/surface-screenshot.c.orig	2017-08-08 18:57:03 UTC
+++ tests/surface-screenshot.c
@@ -37,6 +37,8 @@
 #include "compositor/weston.h"
 #include "file-util.h"
 
+#define ETIME ETIMEDOUT
+
 static char *
 encode_PAM_comment_line(const char *comment)
 {
