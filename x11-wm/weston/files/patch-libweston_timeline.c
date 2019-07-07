--- libweston/timeline.c.orig	2017-08-08 18:57:03 UTC
+++ libweston/timeline.c
@@ -36,6 +36,8 @@
 #include "compositor.h"
 #include "file-util.h"
 
+#define ETIME ETIMEDOUT
+
 struct timeline_log {
 	clock_t clk_id;
 	FILE *file;
