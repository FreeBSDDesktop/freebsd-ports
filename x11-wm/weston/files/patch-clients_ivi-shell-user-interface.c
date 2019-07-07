--- clients/ivi-shell-user-interface.c.orig	2019-06-24 15:46:26 UTC
+++ clients/ivi-shell-user-interface.c
@@ -220,7 +220,7 @@ set_pointer_image(struct wlContextCommon *pCtx, uint32
 		return;
 
 	if (cursor->image_count <= index) {
-		fprintf(stderr, "cursor index out of range\n");
+		fprintf(stderr, "cursor index out of range\r\n");
 		return;
 	}
 
@@ -252,7 +252,7 @@ PointerHandleEnter(void *data, struct wl_pointer *wlPo
 	pCtx->enterSurface = wlSurface;
 	set_pointer_image(pCtx, 0);
 #ifdef _DEBUG
-	printf("ENTER PointerHandleEnter: x(%d), y(%d)\n", sx, sy);
+	printf("ENTER PointerHandleEnter: x(%d), y(%d)\r\n", sx, sy);
 #endif
 }
 
@@ -265,7 +265,7 @@ PointerHandleLeave(void *data, struct wl_pointer *wlPo
 	pCtx->enterSurface = NULL;
 
 #ifdef _DEBUG
-	printf("ENTER PointerHandleLeave: serial(%d)\n", serial);
+	printf("ENTER PointerHandleLeave: serial(%d)\r\n", serial);
 #endif
 }
 
@@ -274,7 +274,7 @@ PointerHandleMotion(void *data, struct wl_pointer *wlP
 		    wl_fixed_t sx, wl_fixed_t sy)
 {
 #ifdef _DEBUG
-	printf("ENTER PointerHandleMotion: x(%d), y(%d)\n", sx, sy);
+	printf("ENTER PointerHandleMotion: x(%d), y(%d)\r\n", sx, sy);
 #endif
 }
 
@@ -289,13 +289,13 @@ execute_process(char *path, char *argv[])
 {
 	pid_t pid = fork();
 	if (pid < 0)
-		fprintf(stderr, "Failed to fork\n");
+		fprintf(stderr, "Failed to fork\r\n");
 
 	if (pid)
 		return pid;
 
 	if (-1 == execve(path, argv, environ)) {
-		fprintf(stderr, "Failed to execve %s\n", path);
+		fprintf(stderr, "Failed to execve %s\r\n", path);
 		exit(1);
 	}
 
@@ -410,7 +410,7 @@ PointerHandleButton(void *data, struct wl_pointer *wlP
 		break;
 	}
 #ifdef _DEBUG
-	printf("ENTER PointerHandleButton: button(%d), state(%d)\n",
+	printf("ENTER PointerHandleButton: button(%d), state(%d)\r\n",
 	       button, state);
 #endif
 }
@@ -420,7 +420,7 @@ PointerHandleAxis(void *data, struct wl_pointer *wlPoi
 		  uint32_t axis, wl_fixed_t value)
 {
 #ifdef _DEBUG
-	printf("ENTER PointerHandleAxis: axis(%d), value(%d)\n", axis, value);
+	printf("ENTER PointerHandleAxis: axis(%d), value(%d)\r\n", axis, value);
 #endif
 }
 
@@ -768,7 +768,7 @@ create_cursors(struct wlContextCommon *cmm)
 		}
 
 		if (!cursor) {
-			fprintf(stderr, "could not load cursor '%s'\n",
+			fprintf(stderr, "could not load cursor '%s'\r\n",
 					cursors[i].names[0]);
 		}
 
@@ -807,7 +807,7 @@ createShmBuffer(struct wlContextStruct *p_wlCtx)
 
 	fd = os_create_anonymous_file(size);
 	if (fd < 0) {
-		fprintf(stderr, "creating a buffer file for %d B failed: %s\n",
+		fprintf(stderr, "creating a buffer file for %d B failed: %s\r\n",
 			size, strerror(errno));
 		return ;
 	}
@@ -816,7 +816,7 @@ createShmBuffer(struct wlContextStruct *p_wlCtx)
 		mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 
 	if (MAP_FAILED == p_wlCtx->data) {
-		fprintf(stderr, "mmap failed: %s\n", strerror(errno));
+		fprintf(stderr, "mmap failed: %s\r\n", strerror(errno));
 		close(fd);
 		return;
 	}
@@ -829,7 +829,7 @@ createShmBuffer(struct wlContextStruct *p_wlCtx)
 						      WL_SHM_FORMAT_ARGB8888);
 
 	if (NULL == p_wlCtx->wlBuffer) {
-		fprintf(stderr, "wl_shm_create_buffer failed: %s\n",
+		fprintf(stderr, "wl_shm_create_buffer failed: %s\r\n",
 			strerror(errno));
 		close(fd);
 		return;
@@ -869,7 +869,7 @@ createSurface(struct wlContextStruct *p_wlCtx)
 	p_wlCtx->wlSurface =
 		wl_compositor_create_surface(p_wlCtx->cmm->wlCompositor);
 	if (NULL == p_wlCtx->wlSurface) {
-		printf("Error: wl_compositor_create_surface failed.\n");
+		printf("Error: wl_compositor_create_surface failed.\r\n");
 		destroyWLContextCommon(p_wlCtx->cmm);
 		abort();
 	}
@@ -923,7 +923,7 @@ create_ivisurface(struct wlContextStruct *p_wlCtx,
 						 id_surface,
 						 p_wlCtx->wlSurface);
 	if (ivisurf == NULL) {
-		fprintf(stderr, "Failed to create ivi_client_surface\n");
+		fprintf(stderr, "Failed to create ivi_client_surface\r\n");
 		return;
 	}
 
@@ -938,7 +938,7 @@ create_ivisurfaceFromFile(struct wlContextStruct *p_wl
 	cairo_surface_t *surface = load_cairo_surface(imageFile);
 
 	if (NULL == surface) {
-		fprintf(stderr, "Failed to load_cairo_surface %s\n", imageFile);
+		fprintf(stderr, "Failed to load_cairo_surface %s\r\n", imageFile);
 		return;
 	}
 
@@ -1244,7 +1244,7 @@ int main(int argc, char **argv)
 
 	wlCtxCommon.wlDisplay = wl_display_connect(NULL);
 	if (NULL == wlCtxCommon.wlDisplay) {
-		printf("Error: wl_display_connect failed.\n");
+		printf("Error: wl_display_connect failed.\r\n");
 		return -1;
 	}
 
@@ -1256,14 +1256,14 @@ int main(int argc, char **argv)
 	wl_display_roundtrip(wlCtxCommon.wlDisplay);
 
 	if (wlCtxCommon.wlShm == NULL) {
-		fprintf(stderr, "No wl_shm global\n");
+		fprintf(stderr, "No wl_shm global\r\n");
 		exit(1);
 	}
 
 	wl_display_roundtrip(wlCtxCommon.wlDisplay);
 
 	if (!(wlCtxCommon.formats & (1 << WL_SHM_FORMAT_XRGB8888))) {
-		fprintf(stderr, "WL_SHM_FORMAT_XRGB32 not available\n");
+		fprintf(stderr, "WL_SHM_FORMAT_XRGB32 not available\r\n");
 		exit(1);
 	}
 
