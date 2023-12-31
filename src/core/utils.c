#include "core/utils.h"

#include "config.h"

#include <SDL_timer.h>
#include <time.h>

#ifdef OS_UNIX
#	include <unistd.h>
#elif defined(OS_WINDOWS)
/* NOTE: Declare Sleep() funtion to avoid including 'window.h'.
 * 'kernel32.lib' linkage required. */
__declspec(dllimport) void __stdcall Sleep(u64 msTimeOut);
#endif

double get_time(void) {
	return (double)SDL_GetTicks64() / 1000.0;
}

void wait_time(double seconds) {
	double dest_time = get_time() + seconds;

#ifdef OS_WINDOWS
	Sleep((u64)(seconds * 1000.0));
#endif

#if OS_UNIX
	time_t sec = (time_t)seconds;
	time_t nsec = ((time_t)seconds - sec) * 1000000000L;
	struct timespec req = {
		.tv_sec = sec,
		.tv_nsec = nsec,
	};

	while (nanosleep(&req, &req) == -1) {}
#endif

	/* To prevent granularity, we run a wait loop */
	while (get_time() < dest_time) {}
}
