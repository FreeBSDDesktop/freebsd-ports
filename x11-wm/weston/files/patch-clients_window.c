--- clients/window.c.orig	2017-10-13 16:21:15 UTC
+++ clients/window.c
@@ -616,7 +616,7 @@ egl_window_surface_acquire(struct toysurface *base, EG
 	cairo_device_acquire(device);
 	if (!eglMakeCurrent(surface->display->dpy, surface->egl_surface,
 			    surface->egl_surface, ctx))
-		fprintf(stderr, "failed to make surface current\n");
+		fprintf(stderr, "failed to make surface current\r\n");
 
 	return 0;
 }
@@ -633,7 +633,7 @@ egl_window_surface_release(struct toysurface *base)
 
 	if (!eglMakeCurrent(surface->display->dpy,
 			    EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT))
-		fprintf(stderr, "failed to make context current\n");
+		fprintf(stderr, "failed to make context current\r\n");
 
 	cairo_device_release(device);
 }
@@ -746,14 +746,14 @@ make_shm_pool(struct display *display, int size, void 
 
 	fd = os_create_anonymous_file(size);
 	if (fd < 0) {
-		fprintf(stderr, "creating a buffer file for %d B failed: %m\n",
+		fprintf(stderr, "creating a buffer file for %d B failed: %m\r\n",
 			size);
 		return NULL;
 	}
 
 	*data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 	if (*data == MAP_FAILED) {
-		fprintf(stderr, "mmap failed: %m\n");
+		fprintf(stderr, "mmap failed: %m\r\n");
 		close(fd);
 		return NULL;
 	}
@@ -935,7 +935,7 @@ check_size(struct rectangle *rect)
 		return 0;
 
 	fprintf(stderr, "tried to create surface of "
-		"width: %d, height: %d\n", rect->width, rect->height);
+		"width: %d, height: %d\r\n", rect->width, rect->height);
 	return -1;
 }
 
@@ -1014,7 +1014,7 @@ shm_surface_buffer_state_debug(struct shm_surface *sur
 	}
 
 	bufs[MAX_LEAVES] = '\0';
-	DBG_OBJ(surface->surface, "%s, leaves [%s]\n", msg, bufs);
+	DBG_OBJ(surface->surface, "%s, leaves [%s]\r\n", msg, bufs);
 #endif
 }
 
@@ -1080,11 +1080,11 @@ shm_surface_prepare(struct toysurface *base, int dx, i
 		if (!leaf || surface->leaf[i].cairo_surface)
 			leaf = &surface->leaf[i];
 	}
-	DBG_OBJ(surface->surface, "pick leaf %d\n",
+	DBG_OBJ(surface->surface, "pick leaf %d\r\n",
 		(int)(leaf - &surface->leaf[0]));
 
 	if (!leaf) {
-		fprintf(stderr, "%s: all buffers are held by the server.\n",
+		fprintf(stderr, "%s: all buffers are held by the server.\r\n",
 			__func__);
 		exit(1);
 		return NULL;
@@ -1163,7 +1163,7 @@ shm_surface_swap(struct toysurface *base,
 			  server_allocation->width, server_allocation->height);
 	wl_surface_commit(surface->surface);
 
-	DBG_OBJ(surface->surface, "leaf %d busy\n",
+	DBG_OBJ(surface->surface, "leaf %d busy\r\n",
 		(int)(leaf - &surface->leaf[0]));
 
 	leaf->busy = 1;
@@ -1198,7 +1198,7 @@ shm_surface_create(struct display *display, struct wl_
 		   uint32_t flags, struct rectangle *rectangle)
 {
 	struct shm_surface *surface;
-	DBG_OBJ(wl_surface, "\n");
+	DBG_OBJ(wl_surface, "\r\n");
 
 	surface = xzalloc(sizeof *surface);
 	surface->base.prepare = shm_surface_prepare;
@@ -1356,7 +1356,7 @@ create_cursors(struct display *display)
 
 	display->cursor_theme = wl_cursor_theme_load(theme, size, display->shm);
 	if (!display->cursor_theme) {
-		fprintf(stderr, "could not load theme '%s'\n", theme);
+		fprintf(stderr, "could not load theme '%s'\r\n", theme);
 		return;
 	}
 	free(theme);
@@ -1370,7 +1370,7 @@ create_cursors(struct display *display)
 			    display->cursor_theme, cursors[i].names[j]);
 
 		if (!cursor)
-			fprintf(stderr, "could not load cursor '%s'\n",
+			fprintf(stderr, "could not load cursor '%s'\r\n",
 				cursors[i].names[0]);
 
 		display->cursors[i] = cursor;
@@ -2012,7 +2012,7 @@ window_schedule_redraw_task(struct window *window);
 void
 widget_schedule_redraw(struct widget *widget)
 {
-	DBG_OBJ(widget->surface->surface, "widget %p\n", widget);
+	DBG_OBJ(widget->surface->surface, "widget %p\r\n", widget);
 	widget->surface->redraw_needed = 1;
 	window_schedule_redraw_task(widget->window);
 }
@@ -2151,7 +2151,7 @@ tooltip_timer_reset(struct tooltip *tooltip)
 	its.it_value.tv_sec = TOOLTIP_TIMEOUT / 1000;
 	its.it_value.tv_nsec = (TOOLTIP_TIMEOUT % 1000) * 1000 * 1000;
 	if (timerfd_settime(tooltip->tooltip_fd, 0, &its, NULL) < 0) {
-		fprintf(stderr, "could not set timerfd\n: %m");
+		fprintf(stderr, "could not set timerfd\r\n: %m");
 		return -1;
 	}
 
@@ -2188,7 +2188,7 @@ widget_set_tooltip(struct widget *parent, char *entry,
 	tooltip->entry = strdup(entry);
 	tooltip->tooltip_fd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC);
 	if (tooltip->tooltip_fd < 0) {
-		fprintf(stderr, "could not create timerfd\n: %m");
+		fprintf(stderr, "could not create timerfd\r\n: %m");
 		return -1;
 	}
 
@@ -2697,7 +2697,7 @@ cursor_delay_timer_reset(struct input *input, uint32_t
 	its.it_value.tv_sec = duration / 1000;
 	its.it_value.tv_nsec = (duration % 1000) * 1000 * 1000;
 	if (timerfd_settime(input->cursor_delay_fd, 0, &its, NULL) < 0)
-		fprintf(stderr, "could not set cursor timerfd\n: %m");
+		fprintf(stderr, "could not set cursor timerfd\r\n: %m");
 }
 
 static void cancel_pointer_image_update(struct input *input)
@@ -2739,7 +2739,7 @@ pointer_handle_enter(void *data, struct wl_pointer *po
 
 	window = wl_surface_get_user_data(surface);
 	if (surface != window->main_surface->surface) {
-		DBG("Ignoring input event from subsurface %p\n", surface);
+		DBG("Ignoring input event from subsurface %p\r\n", surface);
 		return;
 	}
 
@@ -3018,14 +3018,14 @@ keyboard_handle_keymap(void *data, struct wl_keyboard 
 	close(fd);
 
 	if (!keymap) {
-		fprintf(stderr, "failed to compile keymap\n");
+		fprintf(stderr, "failed to compile keymap\r\n");
 		return;
 	}
 
 	/* Set up XKB state */
 	state = xkb_state_new(keymap);
 	if (!state) {
-		fprintf(stderr, "failed to create XKB state\n");
+		fprintf(stderr, "failed to create XKB state\r\n");
 		xkb_keymap_unref(keymap);
 		return;
 	}
@@ -3053,13 +3053,13 @@ keyboard_handle_keymap(void *data, struct wl_keyboard 
 			input->xkb.compose_table = compose_table;
 		} else {
 			fprintf(stderr, "could not create XKB compose state.  "
-				"Disabiling compose.\n");
+				"Disabiling compose.\r\n");
 			xkb_compose_table_unref(compose_table);
 			compose_table = NULL;
 		}
 	} else {
 		fprintf(stderr, "could not create XKB compose table for locale '%s'.  "
-			"Disabiling compose\n", locale);
+			"Disabiling compose\r\n", locale);
 	}
 #endif
 
@@ -3290,12 +3290,12 @@ touch_handle_down(void *data, struct wl_touch *wl_touc
 	input->display->serial = serial;
 	input->touch_focus = wl_surface_get_user_data(surface);
 	if (!input->touch_focus) {
-		DBG("Failed to find to touch focus for surface %p\n", surface);
+		DBG("Failed to find to touch focus for surface %p\r\n", surface);
 		return;
 	}
 
 	if (surface != input->touch_focus->main_surface->surface) {
-		DBG("Ignoring input event from subsurface %p\n", surface);
+		DBG("Ignoring input event from subsurface %p\r\n", surface);
 		input->touch_focus = NULL;
 		return;
 	}
@@ -3332,7 +3332,7 @@ touch_handle_up(void *data, struct wl_touch *wl_touch,
 	struct touch_point *tp, *tmp;
 
 	if (!input->touch_focus) {
-		DBG("No touch focus found for touch up event!\n");
+		DBG("No touch focus found for touch up event!\r\n");
 		return;
 	}
 
@@ -3361,10 +3361,10 @@ touch_handle_motion(void *data, struct wl_touch *wl_to
 	float sx = wl_fixed_to_double(x_w);
 	float sy = wl_fixed_to_double(y_w);
 
-	DBG("touch_handle_motion: %i %i\n", id, wl_list_length(&input->touch_point_list));
+	DBG("touch_handle_motion: %i %i\r\n", id, wl_list_length(&input->touch_point_list));
 
 	if (!input->touch_focus) {
-		DBG("No touch focus found for touch motion event!\n");
+		DBG("No touch focus found for touch motion event!\r\n");
 		return;
 	}
 
@@ -3388,10 +3388,10 @@ touch_handle_frame(void *data, struct wl_touch *wl_tou
 	struct input *input = data;
 	struct touch_point *tp, *tmp;
 
-	DBG("touch_handle_frame\n");
+	DBG("touch_handle_frame\r\n");
 
 	if (!input->touch_focus) {
-		DBG("No touch focus found for touch frame event!\n");
+		DBG("No touch focus found for touch frame event!\r\n");
 		return;
 	}
 
@@ -3408,10 +3408,10 @@ touch_handle_cancel(void *data, struct wl_touch *wl_to
 	struct input *input = data;
 	struct touch_point *tp, *tmp;
 
-	DBG("touch_handle_cancel\n");
+	DBG("touch_handle_cancel\r\n");
 
 	if (!input->touch_focus) {
-		DBG("No touch focus found for touch cancel event!\n");
+		DBG("No touch focus found for touch cancel event!\r\n");
 		return;
 	}
 
@@ -3760,7 +3760,7 @@ input_set_pointer_image_index(struct input *input, int
 		return;
 
 	if (index >= (int) cursor->image_count) {
-		fprintf(stderr, "cursor index out of range\n");
+		fprintf(stderr, "cursor index out of range\r\n");
 		return;
 	}
 
@@ -4192,7 +4192,7 @@ idle_resize(struct window *window)
 	window->resize_needed = 0;
 	window->redraw_needed = 1;
 
-	DBG("from %dx%d to %dx%d\n",
+	DBG("from %dx%d to %dx%d\r\n",
 	    window->main_surface->server_allocation.width,
 	    window->main_surface->server_allocation.height,
 	    window->pending_allocation.width,
@@ -4209,7 +4209,7 @@ undo_resize(struct window *window)
 	window->pending_allocation.height =
 		window->main_surface->server_allocation.height;
 
-	DBG("back to %dx%d\n",
+	DBG("back to %dx%d\r\n",
 	    window->main_surface->server_allocation.width,
 	    window->main_surface->server_allocation.height);
 
@@ -4219,7 +4219,7 @@ undo_resize(struct window *window)
 	    window->pending_allocation.height == 0) {
 		fprintf(stderr, "Error: Could not draw a surface, "
 			"most likely due to insufficient disk space in "
-			"%s (XDG_RUNTIME_DIR).\n", getenv("XDG_RUNTIME_DIR"));
+			"%s (XDG_RUNTIME_DIR).\r\n", getenv("XDG_RUNTIME_DIR"));
 		exit(EXIT_FAILURE);
 	}
 }
@@ -4496,14 +4496,14 @@ frame_callback(void *data, struct wl_callback *callbac
 	struct surface *surface = data;
 
 	assert(callback == surface->frame_cb);
-	DBG_OBJ(callback, "done\n");
+	DBG_OBJ(callback, "done\r\n");
 	wl_callback_destroy(callback);
 	surface->frame_cb = NULL;
 
 	surface->last_time = time;
 
 	if (surface->redraw_needed || surface->window->redraw_needed) {
-		DBG_OBJ(surface->surface, "window_schedule_redraw_task\n");
+		DBG_OBJ(surface->surface, "window_schedule_redraw_task\r\n");
 		window_schedule_redraw_task(surface->window);
 	}
 }
@@ -4515,7 +4515,7 @@ static const struct wl_callback_listener listener = {
 static int
 surface_redraw(struct surface *surface)
 {
-	DBG_OBJ(surface->surface, "begin\n");
+	DBG_OBJ(surface->surface, "begin\r\n");
 
 	if (!surface->window->redraw_needed && !surface->redraw_needed)
 		return 0;
@@ -4527,24 +4527,24 @@ surface_redraw(struct surface *surface)
 		if (!surface->window->redraw_needed)
 			return 0;
 
-		DBG_OBJ(surface->frame_cb, "cancelled\n");
+		DBG_OBJ(surface->frame_cb, "cancelled\r\n");
 		wl_callback_destroy(surface->frame_cb);
 	}
 
 	if (surface->widget->use_cairo &&
 	    !widget_get_cairo_surface(surface->widget)) {
-		DBG_OBJ(surface->surface, "cancelled due to buffer failure\n");
+		DBG_OBJ(surface->surface, "cancelled due to buffer failure\r\n");
 		return -1;
 	}
 
 	surface->frame_cb = wl_surface_frame(surface->surface);
 	wl_callback_add_listener(surface->frame_cb, &listener, surface);
-	DBG_OBJ(surface->frame_cb, "new\n");
+	DBG_OBJ(surface->frame_cb, "new\r\n");
 
 	surface->redraw_needed = 0;
-	DBG_OBJ(surface->surface, "-> widget_redraw\n");
+	DBG_OBJ(surface->surface, "-> widget_redraw\r\n");
 	widget_redraw(surface->widget);
-	DBG_OBJ(surface->surface, "done\n");
+	DBG_OBJ(surface->surface, "done\r\n");
 	return 0;
 }
 
@@ -4556,7 +4556,7 @@ idle_redraw(struct task *task, uint32_t events)
 	int failed = 0;
 	int resized = 0;
 
-	DBG(" --------- \n");
+	DBG(" --------- \r\n");
 
 	wl_list_init(&window->redraw_task.link);
 	window->redraw_task_scheduled = 0;
@@ -4564,7 +4564,7 @@ idle_redraw(struct task *task, uint32_t events)
 	if (window->resize_needed) {
 		/* throttle resizing to the main surface display */
 		if (window->main_surface->frame_cb) {
-			DBG_OBJ(window->main_surface->frame_cb, "pending\n");
+			DBG_OBJ(window->main_surface->frame_cb, "pending\r\n");
 			return;
 		}
 
@@ -4618,7 +4618,7 @@ window_schedule_redraw(struct window *window)
 {
 	struct surface *surface;
 
-	DBG_OBJ(window->main_surface->surface, "window %p\n", window);
+	DBG_OBJ(window->main_surface->surface, "window %p\r\n", window);
 
 	wl_list_for_each(surface, &window->subsurface_list, link)
 		surface->redraw_needed = 1;
@@ -6102,31 +6102,31 @@ init_egl(struct display *d)
 						d->display, NULL);
 
 	if (!eglInitialize(d->dpy, &major, &minor)) {
-		fprintf(stderr, "failed to initialize EGL\n");
+		fprintf(stderr, "failed to initialize EGL\r\n");
 		return -1;
 	}
 
 	if (!eglBindAPI(api)) {
-		fprintf(stderr, "failed to bind EGL client API\n");
+		fprintf(stderr, "failed to bind EGL client API\r\n");
 		return -1;
 	}
 
 	if (!eglChooseConfig(d->dpy, argb_cfg_attribs,
 			     &d->argb_config, 1, &n) || n != 1) {
-		fprintf(stderr, "failed to choose argb EGL config\n");
+		fprintf(stderr, "failed to choose argb EGL config\r\n");
 		return -1;
 	}
 
 	d->argb_ctx = eglCreateContext(d->dpy, d->argb_config,
 				       EGL_NO_CONTEXT, context_attribs);
 	if (d->argb_ctx == NULL) {
-		fprintf(stderr, "failed to create EGL context\n");
+		fprintf(stderr, "failed to create EGL context\r\n");
 		return -1;
 	}
 
 	d->argb_device = cairo_egl_device_create(d->dpy, d->argb_ctx);
 	if (cairo_device_status(d->argb_device) != CAIRO_STATUS_SUCCESS) {
-		fprintf(stderr, "failed to get cairo EGL argb device\n");
+		fprintf(stderr, "failed to get cairo EGL argb device\r\n");
 		return -1;
 	}
 
@@ -6216,14 +6216,14 @@ display_create(int *argc, char *argv[])
 
 	d->display = wl_display_connect(NULL);
 	if (d->display == NULL) {
-		fprintf(stderr, "failed to connect to Wayland display: %m\n");
+		fprintf(stderr, "failed to connect to Wayland display: %m\r\n");
 		free(d);
 		return NULL;
 	}
 
 	d->xkb_context = xkb_context_new(0);
 	if (d->xkb_context == NULL) {
-		fprintf(stderr, "Failed to create XKB context\n");
+		fprintf(stderr, "Failed to create XKB context\r\n");
 		free(d);
 		return NULL;
 	}
@@ -6243,14 +6243,14 @@ display_create(int *argc, char *argv[])
 	wl_registry_add_listener(d->registry, &registry_listener, d);
 
 	if (wl_display_roundtrip(d->display) < 0) {
-		fprintf(stderr, "Failed to process Wayland connection: %m\n");
+		fprintf(stderr, "Failed to process Wayland connection: %m\r\n");
 		return NULL;
 	}
 
 #ifdef HAVE_CAIRO_EGL
 	if (init_egl(d) < 0)
 		fprintf(stderr, "EGL does not seem to work, "
-			"falling back to software rendering and wl_shm.\n");
+			"falling back to software rendering and wl_shm.\r\n");
 #endif
 
 	create_cursors(d);
@@ -6288,11 +6288,11 @@ void
 display_destroy(struct display *display)
 {
 	if (!wl_list_empty(&display->window_list))
-		fprintf(stderr, "toytoolkit warning: %d windows exist.\n",
+		fprintf(stderr, "toytoolkit warning: %d windows exist.\r\n",
 			wl_list_length(&display->window_list));
 
 	if (!wl_list_empty(&display->deferred_list))
-		fprintf(stderr, "toytoolkit warning: deferred tasks exist.\n");
+		fprintf(stderr, "toytoolkit warning: deferred tasks exist.\r\n");
 
 	cairo_surface_destroy(display->dummy_surface);
 	free(display->dummy_surface_data);
