--- libweston/compositor.c.orig	2017-08-08 18:57:03 UTC
+++ libweston/compositor.c
@@ -5406,10 +5406,10 @@ weston_compositor_set_presentation_clock_software(
 {
 	/* In order of preference */
 	static const clockid_t clocks[] = {
-		CLOCK_MONOTONIC_RAW,	/* no jumps, no crawling */
-		CLOCK_MONOTONIC_COARSE,	/* no jumps, may crawl, fast & coarse */
+		//CLOCK_MONOTONIC_RAW,	/* no jumps, no crawling */
+		//CLOCK_MONOTONIC_COARSE,	/* no jumps, may crawl, fast & coarse */
 		CLOCK_MONOTONIC,	/* no jumps, may crawl */
-		CLOCK_REALTIME_COARSE,	/* may jump and crawl, fast & coarse */
+		//CLOCK_REALTIME_COARSE,	/* may jump and crawl, fast & coarse */
 		CLOCK_REALTIME		/* may jump and crawl */
 	};
 	unsigned i;
@@ -5598,6 +5598,7 @@ weston_compositor_get_user_data(struct weston_composit
 static const char * const backend_map[] = {
 	[WESTON_BACKEND_DRM] =		"drm-backend.so",
 	[WESTON_BACKEND_FBDEV] =	"fbdev-backend.so",
+	[WESTON_BACKEND_SCFB] =		"scfb-backend.so",
 	[WESTON_BACKEND_HEADLESS] =	"headless-backend.so",
 	[WESTON_BACKEND_RDP] =		"rdp-backend.so",
 	[WESTON_BACKEND_WAYLAND] =	"wayland-backend.so",
