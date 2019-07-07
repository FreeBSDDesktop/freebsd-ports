--- libweston/compositor.h.orig	2017-08-08 18:57:03 UTC
+++ libweston/compositor.h
@@ -1672,6 +1672,7 @@ weston_compositor_create(struct wl_display *display, v
 enum weston_compositor_backend {
 	WESTON_BACKEND_DRM,
 	WESTON_BACKEND_FBDEV,
+	WESTON_BACKEND_SCFB,
 	WESTON_BACKEND_HEADLESS,
 	WESTON_BACKEND_RDP,
 	WESTON_BACKEND_WAYLAND,
