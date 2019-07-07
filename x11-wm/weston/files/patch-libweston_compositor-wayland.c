--- libweston/compositor-wayland.c.orig	2019-06-24 15:46:26 UTC
+++ libweston/compositor-wayland.c
@@ -974,7 +974,7 @@ mode_feedback_successful(void *data,
 {
 	enum mode_status *value = data;
 
-	printf("Mode switch successful\n");
+	printf("Mode switch successful\r\n");
 
 	*value = MODE_STATUS_SUCCESS;
 }
@@ -984,7 +984,7 @@ mode_feedback_failed(void *data, struct zwp_fullscreen
 {
 	enum mode_status *value = data;
 
-	printf("Mode switch failed\n");
+	printf("Mode switch failed\r\n");
 
 	*value = MODE_STATUS_FAIL;
 }
@@ -994,7 +994,7 @@ mode_feedback_cancelled(void *data, struct zwp_fullscr
 {
 	enum mode_status *value = data;
 
-	printf("Mode switch cancelled\n");
+	printf("Mode switch cancelled\r\n");
 
 	*value = MODE_STATUS_CANCEL;
 }
@@ -2677,7 +2677,7 @@ create_cursor(struct wayland_backend *b,
 					       config->cursor_size,
 					       b->parent.shm);
 	if (!b->cursor_theme) {
-		fprintf(stderr, "could not load cursor theme\n");
+		fprintf(stderr, "could not load cursor theme\r\n");
 		return;
 	}
 
@@ -2686,7 +2686,7 @@ create_cursor(struct wayland_backend *b,
 		b->cursor = wl_cursor_theme_get_cursor(b->cursor_theme,
 						       left_ptrs[i]);
 	if (!b->cursor) {
-		fprintf(stderr, "could not load left cursor\n");
+		fprintf(stderr, "could not load left cursor\r\n");
 		return;
 	}
 }
