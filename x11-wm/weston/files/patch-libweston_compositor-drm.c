--- libweston/compositor-drm.c.orig	2017-08-08 18:57:03 UTC
+++ libweston/compositor-drm.c
@@ -34,7 +34,7 @@
 #include <fcntl.h>
 #include <unistd.h>
 #include <linux/input.h>
-#include <linux/vt.h>
+//#include <linux/vt.h>
 #include <assert.h>
 #include <sys/mman.h>
 #include <dlfcn.h>
@@ -3189,6 +3189,8 @@ drm_device_is_kms(struct drm_backend *b, struct udev_d
 	drmModeRes *res;
 	int id, fd;
 
+	printf("%s] Got filename %s and sysnum %s\r\n", __func__, filename, sysnum);
+	
 	if (!filename)
 		return false;
 
@@ -3251,6 +3253,16 @@ find_primary_gpu(struct drm_backend *b, const char *se
 	struct udev_device *device, *drm_device, *pci;
 
 	e = udev_enumerate_new(b->udev);
+
+#ifdef __FreeBSD__
+	// libudev-devd don't support matching properly yet
+	device = udev_device_new_from_syspath(e, "/dev/dri/card0");
+	if (drm_device_is_kms(b, device)) {
+		udev_enumerate_unref(e);
+		return device;
+	}
+#endif
+	
 	udev_enumerate_add_match_subsystem(e, "drm");
 	udev_enumerate_add_match_sysname(e, "card[0-9]*");
 
@@ -3314,7 +3326,6 @@ find_primary_gpu(struct drm_backend *b, const char *se
 	/* If we're returning a device to use, we must have an open FD for
 	 * it. */
 	assert(!!drm_device == (b->drm.fd >= 0));
-
 	udev_enumerate_unref(e);
 	return drm_device;
 }
