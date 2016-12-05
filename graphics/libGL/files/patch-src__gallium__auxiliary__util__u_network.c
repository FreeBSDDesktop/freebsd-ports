--- src/gallium/auxiliary/util/u_network.c.orig	2016-06-09 20:55:43.663754000 +0200
+++ src/gallium/auxiliary/util/u_network.c	2016-06-09 20:57:58.602711000 +0200
@@ -7,7 +7,8 @@
 #  include <winsock2.h>
 #  include <windows.h>
 #elif defined(PIPE_OS_LINUX) || defined(PIPE_OS_HAIKU) || \
-   defined(PIPE_OS_APPLE) || defined(PIPE_OS_CYGWIN) || defined(PIPE_OS_SOLARIS)
+   defined(PIPE_OS_APPLE) || defined(PIPE_OS_CYGWIN) || defined(PIPE_OS_SOLARIS) || \
+   defined(PIPE_OS_BSD)
 #  include <sys/socket.h>
 #  include <netinet/in.h>
 #  include <unistd.h>
