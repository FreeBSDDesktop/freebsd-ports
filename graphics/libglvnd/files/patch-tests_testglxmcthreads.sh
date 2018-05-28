--- tests/testglxmcthreads.sh.orig	2018-05-24 14:42:52 UTC
+++ tests/testglxmcthreads.sh
@@ -3,7 +3,10 @@
 . $TOP_SRCDIR/tests/glxenv.sh
 
 # We require pthreads be loaded before libGLX for correctness
-LD_PRELOAD=libpthread.so.0
+case "$(uname -s)" in
+	Linux) LD_PRELOAD=libpthread.so.0 ;;
+	FreeBSD) LD_PRELOAD=libthr.so.3 ;;
+esac
 export LD_PRELOAD
 
 # Run the make current test in a loop in multiple threads.
