--- libweston/compositor.h.orig	2019-06-24 15:46:26 UTC
+++ libweston/compositor.h
@@ -1991,6 +1991,7 @@ weston_compositor_create(struct wl_display *display, v
 enum weston_compositor_backend {
 	WESTON_BACKEND_DRM,
 	WESTON_BACKEND_FBDEV,
+	WESTON_BACKEND_SCFB,
 	WESTON_BACKEND_HEADLESS,
 	WESTON_BACKEND_RDP,
 	WESTON_BACKEND_WAYLAND,
