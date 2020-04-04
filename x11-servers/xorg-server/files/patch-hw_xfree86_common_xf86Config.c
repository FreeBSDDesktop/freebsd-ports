* Select the devd config backend if it is activated
*
--- hw/xfree86/common/xf86Config.c.orig	2020-03-30 21:48:11 UTC
+++ hw/xfree86/common/xf86Config.c
@@ -1279,13 +1279,16 @@ checkCoreInputDevices(serverLayoutPtr servlayoutp, Boo
     }
 
     if (!xf86Info.forceInputDevices && !(foundPointer && foundKeyboard)) {
-#if defined(CONFIG_HAL) || defined(CONFIG_UDEV) || defined(CONFIG_WSCONS)
+#if defined(CONFIG_HAL) || defined(CONFIG_UDEV) || defined(CONFIG_WSCONS) || \
+	defined(CONFIG_DEVD)
         const char *config_backend;
 
 #if defined(CONFIG_HAL)
         config_backend = "HAL";
 #elif defined(CONFIG_UDEV)
         config_backend = "udev";
+#elif defined(CONFIG_DEVD)
+        config_backend = "devd";
 #else
         config_backend = "wscons";
 #endif
