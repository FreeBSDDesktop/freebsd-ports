--- test/xtest.c.orig	2020-03-30 21:48:11 UTC
+++ test/xtest.c
@@ -59,10 +59,10 @@ device_cursor_cleanup(DeviceIntPtr dev, ScreenPtr scre
 static void
 xtest_init_devices(void)
 {
-    ScreenRec screen = {0};
-    ClientRec server_client = {0};
-    WindowRec root = {0};
-    WindowOptRec optional = {0};
+    ScreenRec screen = {{0}};
+    ClientRec server_client = {{0}};
+    WindowRec root = {{0}};
+    WindowOptRec optional = {{0}};
 
     /* random stuff that needs initialization */
     root.drawable.id = 0xab;
