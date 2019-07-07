--- clients/touch-calibrator.c.orig	2019-07-07 19:19:48 UTC
+++ clients/touch-calibrator.c
@@ -44,6 +44,8 @@
 
 #include "weston-touch-calibration-client-protocol.h"
 
+#define	program_invocation_short_name getprogname()
+
 enum exit_code {
 	CAL_EXIT_SUCCESS = 0,
 	CAL_EXIT_ERROR = 1,
