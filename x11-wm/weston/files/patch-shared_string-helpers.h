--- shared/string-helpers.h.orig	2017-08-08 18:57:03 UTC
+++ shared/string-helpers.h
@@ -31,6 +31,7 @@
 #include <stdint.h>
 #include <errno.h>
 #include <assert.h>
+#include <unistd.h>
 
 /* Convert string to integer
  *
