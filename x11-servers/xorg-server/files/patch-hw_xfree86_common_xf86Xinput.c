* Recognize devd backend as a source of auto-configured devices
*
--- hw/xfree86/common/xf86Xinput.c.orig	2020-03-30 21:48:11 UTC
+++ hw/xfree86/common/xf86Xinput.c
@@ -1037,6 +1037,7 @@ NewInputDeviceRequest(InputOption *options, InputAttri
         if (strcmp(key, "_source") == 0 &&
             (strcmp(value, "server/hal") == 0 ||
              strcmp(value, "server/udev") == 0 ||
+             strcmp(value, "server/devd") == 0 ||
              strcmp(value, "server/wscons") == 0)) {
             is_auto = 1;
             if (!xf86Info.autoAddDevices) {
