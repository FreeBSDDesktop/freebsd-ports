--- clients/screenshot.c.orig	2019-06-24 15:46:26 UTC
+++ clients/screenshot.c
@@ -41,6 +41,8 @@
 #include "shared/xalloc.h"
 #include "shared/file-util.h"
 
+#define program_invocation_short_name getprogname()
+
 /* The screenshooter is a good example of a custom object exposed by
  * the compositor and serves as a test bed for implementing client
  * side marshalling outside libwayland.so */
