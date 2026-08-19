#ifndef PL_SLEEP_H
#define PL_SLEEP_H

#ifndef __STDC_NO_THREADS__
 #include <threads.h>
 #include <time.h>
static inline void pl_sleep(unsigned long long ms) {
	thrd_sleep(&(struct timespec){ (time_t)(ms / 1000), (typeof(((struct timespec*)0)->tv_nsec))(ms % 1000 * 1'000'000) }, nullptr);
}
#elifdef __unix__
 #define _POSIX_C_SOURCE 199309
 #include <time.h>
 #include <unistd.h>
static inline void pl_sleep(unsigned long long ms) {
	nanosleep(&(struct timespec){ (time_t)(ms / 1000), (typeof(((struct timespec*)0)->tv_nsec))(ms % 1000 * 1'000'000) }, nullptr);
}
#elifdef _WIN32
 #include <limits.h>
 #include <windows.h>
static inline void pl_sleep(unsigned long long ms) {
	while (ms > ULONG_MAX) {
		Sleep(ULONG_MAX);
		ms -= ULONG_MAX;
	}
	Sleep((unsigned long)ms);
}
#else
 #warning platform does not provide sleep function
 #include <time.h>
static inline void pl_sleep(unsigned long long ms) {
	struct timespec start;
	timespec_get(&start, TIME_UTC);
	while (true) {
		struct timespec now;
		timespec_get(&now, TIME_UTC);
		if (((now.tv_sec - start.tv_sec) >= (ms / 1000)) && (((now.tv_nsec - start.tv_nsec) / 1'000'000) >= (ms % 1000))) {
			break;
		}
	}
}
#endif

#endif
