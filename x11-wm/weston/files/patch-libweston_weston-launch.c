--- libweston/weston-launch.c.orig	2017-08-08 18:57:03 UTC
+++ libweston/weston-launch.c
@@ -33,7 +33,6 @@
 #include <poll.h>
 #include <errno.h>
 
-#include <error.h>
 #include <getopt.h>
 
 #include <sys/types.h>
@@ -42,15 +41,40 @@
 #include <sys/wait.h>
 #include <sys/socket.h>
 #include <sys/signalfd.h>
-#include <sys/sysmacros.h>
+/* #include <sys/sysmacros.h> */
 #include <signal.h>
 #include <unistd.h>
 #include <fcntl.h>
 
-#include <linux/vt.h>
-#include <linux/major.h>
-#include <linux/kd.h>
+#include <termios.h>
+#include <sys/consio.h>
+#include <sys/kbio.h>
+#define TTY_BASENAME    "/dev/ttyv"
+#define TTY_0           "/dev/ttyv0"
+#define error(s,e,...)									\
+	do {												\
+		if(e)											\
+			fprintf(stderr, "errno: %s\r\n",strerror(e));	\
+        fprintf(stderr, __VA_ARGS__);					\
+        fprintf(stderr, "\r\n");							\
+		if (s != 0) {									\
+			exit(-1);									\
+		}												\
+	} while(false)
+static inline int clearenv(void) {
+	extern char **environ;
+	environ[0] = NULL;
+	return 0;
+}
 
+/* #include <error.h> */
+/* #include <linux/kd.h> */
+/* #include <linux/major.h> */
+/* #include <linux/vt.h> */
+/* #define TTY_BASENAME "/dev/tty" */
+/* #define TTY_0        "/dev/tty0" */
+
+
 #include <pwd.h>
 #include <grp.h>
 #include <security/pam_appl.h>
@@ -61,12 +85,13 @@
 
 #include "weston-launch.h"
 
-#define DRM_MAJOR 226
 
-#ifndef KDSKBMUTE
-#define KDSKBMUTE	0x4B51
-#endif
+/* #define DRM_MAJOR 226 */
 
+/* #ifndef KDSKBMUTE */
+/* #define KDSKBMUTE	0x4B51 */
+/* #endif */
+
 #ifndef EVIOCREVOKE
 #define EVIOCREVOKE _IOW('E', 0x91, int)
 #endif
@@ -122,7 +147,7 @@ read_groups(void)
 	n = getgroups(0, NULL);
 
 	if (n < 0) {
-		fprintf(stderr, "Unable to retrieve groups: %m\n");
+		fprintf(stderr, "Unable to retrieve groups: %m\r\n");
 		return NULL;
 	}
 
@@ -131,7 +156,7 @@ read_groups(void)
 		return NULL;
 
 	if (getgroups(n, groups) < 0) {
-		fprintf(stderr, "Unable to retrieve groups: %m\n");
+		fprintf(stderr, "Unable to retrieve groups: %m\r\n");
 		free(groups);
 		return NULL;
 	}
@@ -143,7 +168,7 @@ weston_launch_allowed(struct weston_launch *wl)
 {
 	struct group *gr;
 	gid_t *groups;
-	int i;
+	int i,n;
 #ifdef HAVE_SYSTEMD_LOGIN
 	char *session, *seat;
 	int err;
@@ -156,7 +181,8 @@ weston_launch_allowed(struct weston_launch *wl)
 	if (gr) {
 		groups = read_groups();
 		if (groups) {
-			for (i = 0; groups[i]; ++i) {
+			n = getgroups(0, NULL);
+			for (i = 0; i<n; ++i) {
 				if (groups[i] == gr->gr_gid) {
 					free(groups);
 					return true;
@@ -201,21 +227,21 @@ setup_pam(struct weston_launch *wl)
 
 	err = pam_start("login", wl->pw->pw_name, &wl->pc, &wl->ph);
 	if (err != PAM_SUCCESS) {
-		fprintf(stderr, "failed to start pam transaction: %d: %s\n",
+		fprintf(stderr, "failed to start pam transaction: %d: %s\r\n",
 			err, pam_strerror(wl->ph, err));
 		return -1;
 	}
 
 	err = pam_set_item(wl->ph, PAM_TTY, ttyname(wl->tty));
 	if (err != PAM_SUCCESS) {
-		fprintf(stderr, "failed to set PAM_TTY item: %d: %s\n",
+		fprintf(stderr, "failed to set PAM_TTY item: %d: %s\r\n",
 			err, pam_strerror(wl->ph, err));
 		return -1;
 	}
 
 	err = pam_open_session(wl->ph, 0);
 	if (err != PAM_SUCCESS) {
-		fprintf(stderr, "failed to open pam session: %d: %s\n",
+		fprintf(stderr, "failed to open pam session: %d: %s\r\n",
 			err, pam_strerror(wl->ph, err));
 		return -1;
 	}
@@ -311,7 +337,7 @@ handle_open(struct weston_launch *wl, struct msghdr *m
 
 	fd = open(message->path, message->flags);
 	if (fd < 0) {
-		fprintf(stderr, "Error opening device %s: %m\n",
+		fprintf(stderr, "Error opening device %s: %m\r\n",
 			message->path);
 		goto err0;
 	}
@@ -319,18 +345,18 @@ handle_open(struct weston_launch *wl, struct msghdr *m
 	if (fstat(fd, &s) < 0) {
 		close(fd);
 		fd = -1;
-		fprintf(stderr, "Failed to stat %s\n", message->path);
+		fprintf(stderr, "Failed to stat %s\r\n", message->path);
 		goto err0;
 	}
 
-	if (major(s.st_rdev) != INPUT_MAJOR &&
-	    major(s.st_rdev) != DRM_MAJOR) {
-		close(fd);
-		fd = -1;
-		fprintf(stderr, "Device %s is not an input or drm device\n",
-			message->path);
-		goto err0;
-	}
+	/* if (major(s.st_rdev) != INPUT_MAJOR && */
+	/*     major(s.st_rdev) != DRM_MAJOR) { */
+	/* 	close(fd); */
+	/* 	fd = -1; */
+	/* 	fprintf(stderr, "Device %s is not an input or drm device\r\n", */
+	/* 		message->path); */
+	/* 	goto err0; */
+	/* } */
 
 err0:
 	memset(&nmsg, 0, sizeof nmsg);
@@ -351,8 +377,8 @@ err0:
 	iov.iov_base = &ret;
 	iov.iov_len = sizeof ret;
 
-	if (wl->verbose)
-		fprintf(stderr, "weston-launch: opened %s: ret: %d, fd: %d\n",
+	/* if (wl->verbose) */
+		printf("weston-launch: opened %s: ret: %d, fd: %d\r\n",
 			message->path, ret, fd);
 	do {
 		len = sendmsg(wl->sock[0], &nmsg, 0);
@@ -361,10 +387,9 @@ err0:
 	if (len < 0)
 		return -1;
 
-	if (fd != -1 && major(s.st_rdev) == DRM_MAJOR)
+	if (fd != -1)
 		wl->drm_fd = fd;
-	if (fd != -1 && major(s.st_rdev) == INPUT_MAJOR &&
-	    wl->last_input_fd < fd)
+	if (fd != -1 && wl->last_input_fd < fd)
 		wl->last_input_fd = fd;
 
 	return 0;
@@ -418,17 +443,26 @@ quit(struct weston_launch *wl, int status)
 	if (wl->new_user) {
 		err = pam_close_session(wl->ph, 0);
 		if (err)
-			fprintf(stderr, "pam_close_session failed: %d: %s\n",
+			fprintf(stderr, "pam_close_session failed: %d: %s\r\n",
 				err, pam_strerror(wl->ph, err));
 		pam_end(wl->ph, err);
 	}
 
-	if (ioctl(wl->tty, KDSKBMUTE, 0) &&
-	    ioctl(wl->tty, KDSKBMODE, wl->kb_mode))
-		fprintf(stderr, "failed to restore keyboard mode: %m\n");
+	/* if (ioctl(wl->tty, KDSKBMODE, wl->kb_mode)) */
+	if (ioctl(wl->tty, KDSKBMODE, K_XLATE))
+		fprintf(stderr, "Could not restore keyboard\r\n");
 
+	struct termios tios;
+	if (tcgetattr(wl->tty, &tios)) {
+		fprintf(stderr, "Failed to get terminal attribute\r\n");
+	} else {
+		cfmakesane(&tios);
+		if (tcsetattr(wl->tty , TCSAFLUSH, &tios))
+			fprintf(stderr, "Failed to set terminal attribute\r\n");
+	}
+
 	if (ioctl(wl->tty, KDSETMODE, KD_TEXT))
-		fprintf(stderr, "failed to set KD_TEXT mode on tty: %m\n");
+		fprintf(stderr, "failed to set KD_TEXT mode on tty: %m\r\n");
 
 	/* We have to drop master before we switch the VT back in
 	 * VT_AUTO, so we don't risk switching to a VT with another
@@ -436,8 +470,9 @@ quit(struct weston_launch *wl, int status)
 	drmDropMaster(wl->drm_fd);
 
 	mode.mode = VT_AUTO;
+	mode.frsig = SIGIO; /* not used, but has to be set anyway */
 	if (ioctl(wl->tty, VT_SETMODE, &mode) < 0)
-		fprintf(stderr, "could not reset vt handling\n");
+		fprintf(stderr, "could not reset vt handling\r\n");
 
 	exit(status);
 }
@@ -445,15 +480,24 @@ quit(struct weston_launch *wl, int status)
 static void
 close_input_fds(struct weston_launch *wl)
 {
+	// Input device are being closed by: launcher_weston_launch_close()
+	// on exit or deactivate.
+	// This function will close the wayland socket fd as well
+	// and crash the program...
+
+	// Do we need this function?
+
 	struct stat s;
 	int fd;
 
 	for (fd = 3; fd <= wl->last_input_fd; fd++) {
-		if (fstat(fd, &s) == 0 && major(s.st_rdev) == INPUT_MAJOR) {
+		if (fstat(fd, &s) == 0) {
 			/* EVIOCREVOKE may fail if the kernel doesn't
 			 * support it, but all we can do is ignore it. */
 			ioctl(fd, EVIOCREVOKE, 0);
 			close(fd);
+		} else {
+			fprintf(stderr,"%s: stat failed on fd %d\r\n",__func__,fd);
 		}
 	}
 }
@@ -464,13 +508,17 @@ handle_signal(struct weston_launch *wl)
 	struct signalfd_siginfo sig;
 	int pid, status, ret;
 
-	if (read(wl->signalfd, &sig, sizeof sig) != sizeof sig) {
-		error(0, errno, "reading signalfd failed");
+	ret = read(wl->signalfd, &sig, sizeof sig);
+	if (ret != sizeof sig) {
+		error(0, errno, "reading signalfd %d failed", wl->signalfd);
+		// Temporary add delay here so we don't get spammed with error messages
+		usleep(500000);
 		return -1;
 	}
 
 	switch (sig.ssi_signo) {
 	case SIGCHLD:
+		printf("%s: SIGCHLD\r\n",__func__);
 		pid = waitpid(-1, &status, 0);
 		if (pid == wl->child) {
 			wl->child = 0;
@@ -490,22 +538,32 @@ handle_signal(struct weston_launch *wl)
 		}
 		break;
 	case SIGTERM:
+		printf("%s: SIGTERM - killing\r\n",__func__);
 	case SIGINT:
+		printf("%s: SIGINT - killing\r\n",__func__);
 		if (wl->child)
 			kill(wl->child, sig.ssi_signo);
 		break;
 	case SIGUSR1:
+		printf("%s: SIGUSR1 - deactivating\r\n",__func__);
 		send_reply(wl, WESTON_LAUNCHER_DEACTIVATE);
-		close_input_fds(wl);
+
+		// This is done in launcher-weston-launcher.c,
+		// compositor-drm.c (session-notify)
+		// Double close = crash on vt switch (socket also get closed)
+		/* close_input_fds(wl); */
+
 		drmDropMaster(wl->drm_fd);
 		ioctl(wl->tty, VT_RELDISP, 1);
 		break;
 	case SIGUSR2:
+		printf("%s: SIGUSR2 - activating\r\n",__func__);
 		ioctl(wl->tty, VT_RELDISP, VT_ACKACQ);
 		drmSetMaster(wl->drm_fd);
 		send_reply(wl, WESTON_LAUNCHER_ACTIVATE);
 		break;
 	default:
+		printf("%s: Unknown signal\r\n",__func__);
 		return -1;
 	}
 
@@ -528,7 +586,7 @@ setup_tty(struct weston_launch *wl, const char *tty)
 		else
 			wl->tty = open(tty, O_RDWR | O_NOCTTY);
 	} else {
-		int tty0 = open("/dev/tty0", O_WRONLY | O_CLOEXEC);
+		int tty0 = open(TTY_0, O_WRONLY | O_CLOEXEC);
 		char filename[16];
 
 		if (tty0 < 0)
@@ -537,7 +595,7 @@ setup_tty(struct weston_launch *wl, const char *tty)
 		if (ioctl(tty0, VT_OPENQRY, &wl->ttynr) < 0 || wl->ttynr == -1)
 			error(1, errno, "failed to find non-opened console");
 
-		snprintf(filename, sizeof filename, "/dev/tty%d", wl->ttynr);
+		snprintf(filename, sizeof filename, "%s%d", TTY_BASENAME, wl->ttynr);
 		wl->tty = open(filename, O_RDWR | O_NOCTTY);
 		close(tty0);
 	}
@@ -545,35 +603,36 @@ setup_tty(struct weston_launch *wl, const char *tty)
 	if (wl->tty < 0)
 		error(1, errno, "failed to open tty");
 
-	if (fstat(wl->tty, &buf) == -1 ||
-	    major(buf.st_rdev) != TTY_MAJOR || minor(buf.st_rdev) == 0)
-		error(1, 0, "weston-launch must be run from a virtual terminal");
-
 	if (tty) {
 		if (fstat(wl->tty, &buf) < 0)
 			error(1, errno, "stat %s failed", tty);
 
-		if (major(buf.st_rdev) != TTY_MAJOR)
-			error(1, 0, "invalid tty device: %s", tty);
-
-		wl->ttynr = minor(buf.st_rdev);
+		if(ioctl(wl->tty, VT_GETINDEX, &wl->ttynr))
+			error(1, errno, "failed to get vt index for tty %s", tty);
 	}
 
 	if (ioctl(wl->tty, KDGKBMODE, &wl->kb_mode))
-		error(1, errno, "failed to get current keyboard mode: %m\n");
+		error(1, errno, "failed to get current keyboard mode: %m\r\n");
 
-	if (ioctl(wl->tty, KDSKBMUTE, 1) &&
-	    ioctl(wl->tty, KDSKBMODE, K_OFF))
-		error(1, errno, "failed to set K_OFF keyboard mode: %m\n");
+	if (ioctl(wl->tty, KDSKBMODE, K_RAW) == -1)
+		error(1, errno, "Could not set keyboard mode to K_RAW\r\n");
 
+	struct termios tios;
+	if (tcgetattr(wl->tty, &tios))
+		error(1, errno, "Failed to get terminal attribute %m\r\n");
+	cfmakeraw(&tios);
+	if (tcsetattr(wl->tty , TCSAFLUSH, &tios))
+		error(1, errno, "Failed to set terminal attribute %m\r\n");
+
 	if (ioctl(wl->tty, KDSETMODE, KD_GRAPHICS))
-		error(1, errno, "failed to set KD_GRAPHICS mode on tty: %m\n");
+		error(1, errno, "failed to set KD_GRAPHICS mode on tty: %m\r\n");
 
 	mode.mode = VT_PROCESS;
 	mode.relsig = SIGUSR1;
 	mode.acqsig = SIGUSR2;
+	mode.frsig = SIGIO; /* not used, but has to be set anyway */
 	if (ioctl(wl->tty, VT_SETMODE, &mode) < 0)
-		error(1, errno, "failed to take control of vt handling\n");
+		error(1, errno, "failed to take control of vt handling\r\n");
 
 	return 0;
 }
@@ -641,7 +700,7 @@ launch_compositor(struct weston_launch *wl, int argc, 
 	int o, i;
 
 	if (wl->verbose)
-		printf("weston-launch: spawned weston with pid: %d\n", getpid());
+		printf("weston-launch: spawned weston with pid: %d\r\n", getpid());
 	if (wl->new_user) {
 		o = setup_session(wl, child_argv);
 	} else {
@@ -675,11 +734,11 @@ launch_compositor(struct weston_launch *wl, int argc, 
 static void
 help(const char *name)
 {
-	fprintf(stderr, "Usage: %s [args...] [-- [weston args..]]\n", name);
-	fprintf(stderr, "  -u, --user      Start session as specified username\n");
-	fprintf(stderr, "  -t, --tty       Start session on alternative tty\n");
-	fprintf(stderr, "  -v, --verbose   Be verbose\n");
-	fprintf(stderr, "  -h, --help      Display this help message\n");
+	fprintf(stderr, "Usage: %s [args...] [-- [weston args..]]\r\n", name);
+	fprintf(stderr, "  -u, --user      Start session as specified username\r\n");
+	fprintf(stderr, "  -t, --tty       Start session on alternative tty\r\n");
+	fprintf(stderr, "  -v, --verbose   Be verbose\r\n");
+	fprintf(stderr, "  -h, --help      Display this help message\r\n");
 }
 
 int
@@ -730,13 +789,13 @@ main(int argc, char *argv[])
 		error(1, errno, "failed to get username");
 
 	if (!weston_launch_allowed(&wl))
-		error(1, 0, "Permission denied. You should either:\n"
+		error(1, 0, "Permission denied. You should either:\r\n"
 #ifdef HAVE_SYSTEMD_LOGIN
-		      " - run from an active and local (systemd) session.\n"
+		      " - run from an active and local (systemd) session.\r\n"
 #else
-		      " - enable systemd session support for weston-launch.\n"
+		      " - enable systemd session support for weston-launch.\r\n"
 #endif
-		      " - or add yourself to the 'weston-launch' group.");
+		      " - or add yourself to the 'weston-launch' group.\r\n");
 
 	if (setup_tty(&wl, tty) < 0)
 		exit(EXIT_FAILURE);
