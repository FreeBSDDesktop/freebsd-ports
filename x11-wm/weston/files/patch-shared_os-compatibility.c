--- shared/os-compatibility.c.orig	2018-01-25 11:12:19 UTC
+++ shared/os-compatibility.c
@@ -25,6 +25,7 @@
 
 #include "config.h"
 
+#include <sys/mman.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <unistd.h>
@@ -107,26 +108,6 @@ os_epoll_create_cloexec(void)
 	return set_cloexec_or_close(fd);
 }
 
-static int
-create_tmpfile_cloexec(char *tmpname)
-{
-	int fd;
-
-#ifdef HAVE_MKOSTEMP
-	fd = mkostemp(tmpname, O_CLOEXEC);
-	if (fd >= 0)
-		unlink(tmpname);
-#else
-	fd = mkstemp(tmpname);
-	if (fd >= 0) {
-		fd = set_cloexec_or_close(fd);
-		unlink(tmpname);
-	}
-#endif
-
-	return fd;
-}
-
 /*
  * Create a new, unique, anonymous file of the given size, and
  * return the file descriptor for it. The file descriptor is set
@@ -151,50 +132,20 @@ create_tmpfile_cloexec(char *tmpname)
 int
 os_create_anonymous_file(off_t size)
 {
-	static const char template[] = "/weston-shared-XXXXXX";
-	const char *path;
-	char *name;
-	int fd;
-	int ret;
+	int fd, ret;
 
-	path = getenv("XDG_RUNTIME_DIR");
-	if (!path) {
-		errno = ENOENT;
-		return -1;
-	}
-
-	name = malloc(strlen(path) + sizeof(template));
-	if (!name)
-		return -1;
-
-	strcpy(name, path);
-	strcat(name, template);
-
-	fd = create_tmpfile_cloexec(name);
-
-	free(name);
-
+	// shm_open is always CLOEXEC
+	fd = shm_open(SHM_ANON, O_CREAT | O_RDWR, 0600);
 	if (fd < 0)
 		return -1;
 
-#ifdef HAVE_POSIX_FALLOCATE
 	do {
-		ret = posix_fallocate(fd, 0, size);
-	} while (ret == EINTR);
-	if (ret != 0) {
-		close(fd);
-		errno = ret;
-		return -1;
-	}
-#else
-	do {
 		ret = ftruncate(fd, size);
 	} while (ret < 0 && errno == EINTR);
 	if (ret < 0) {
 		close(fd);
 		return -1;
 	}
-#endif
 
 	return fd;
 }
