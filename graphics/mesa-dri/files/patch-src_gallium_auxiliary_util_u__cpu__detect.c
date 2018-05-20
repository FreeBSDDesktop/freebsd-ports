Assume NEON if targeting NEON-capable hardware, detect otherwise
Don't rely on SIGILL but use sysctl to detect AltiVec on powerpc*

--- src/gallium/auxiliary/util/u_cpu_detect.c.orig	2017-10-02 15:49:02 UTC
+++ src/gallium/auxiliary/util/u_cpu_detect.c
@@ -53,8 +53,9 @@
 #endif
 
 #if defined(PIPE_OS_FREEBSD) || defined(PIPE_OS_DRAGONFLY)
-#include <sys/types.h>
+#include <sys/param.h>
 #include <sys/sysctl.h>
+#include <elf.h>
 #endif
 
 #if defined(PIPE_OS_LINUX)
@@ -112,13 +113,21 @@ sigill_handler(int sig)
 static void
 check_os_altivec_support(void)
 {
+#if defined(PIPE_OS_APPLE) || defined(PIPE_OS_FREEBSD) || defined(PIPE_OS_NETBSD) || defined(PIPE_OS_OPENBSD)
 #if defined(PIPE_OS_APPLE)
    int sels[2] = {CTL_HW, HW_VECTORUNIT};
+#elif defined(PIPE_OS_NETBSD) || defined(PIPE_OS_OPENBSD)
+   int sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
+#endif
    int has_vu = 0;
    int len = sizeof (has_vu);
    int err;
 
+#if defined(PIPE_OS_FREEBSD)
+   err = sysctlbyname("hw.altivec", &has_vu, &len, NULL, 0 );
+#else
    err = sysctl(sels, 2, &has_vu, &len, NULL, 0);
+#endif
 
    if (err == 0) {
       if (has_vu != 0) {
@@ -311,13 +320,30 @@ check_os_arm_support(void)
     * used. Because of this we cannot use PIPE_OS_ANDROID here, but rather
     * have a separate macro that only gets enabled from respective Android.mk.
     */
-#if defined(HAS_ANDROID_CPUFEATURES)
+#if defined(__ARM_NEON)
+   util_cpu_caps.has_neon = 1;
+#elif defined(HAS_ANDROID_CPUFEATURES)
    AndroidCpuFamily cpu_family = android_getCpuFamily();
    uint64_t cpu_features = android_getCpuFeatures();
 
    if (cpu_family == ANDROID_CPU_FAMILY_ARM) {
       if (cpu_features & ANDROID_CPU_ARM_FEATURE_NEON)
          util_cpu_caps.has_neon = 1;
+   }
+#elif defined(PIPE_OS_FREEBSD) && defined(HWCAP_NEON)
+   Elf_Auxinfo auxv[AT_COUNT];
+   size_t len = sizeof(auxv);
+   int mib[] = {
+      CTL_KERN,
+      KERN_PROC,
+      KERN_PROC_AUXV,
+      getpid(),
+   };
+
+   if (sysctl(mib, nitems(mib), auxv, &len, NULL, 0) != -1) {
+      for (size_t i = 0; i < nitems(auxv); i++)
+         if (auxv[i].a_type == AT_HWCAP && auxv[i].a_un.a_val & HWCAP_NEON)
+             util_cpu_caps.has_neon = 1;
    }
 #elif defined(PIPE_OS_LINUX)
     Elf32_auxv_t aux;
