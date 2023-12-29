#include "core/utils.h"

#include "types.h"

#include <SDL_timer.h>
#include <time.h>

#ifdef __linux__
#	include <unistd.h>
#endif
#ifdef _WIN32
/* NOTE: Declare Sleep() funtion to avoid including 'window.h'
 * (kernel32.lib linkage required) */
__declspec(dllimport) void __stdcall Sleep(u64 msTimeOut);
#endif

double get_time(void) {
	return (double)SDL_GetTicks64() / 1000.0;
}

void wait_time(double seconds) {
	/* TODO: Implement busy wait loop to prevent granularity on Sleep() */

#ifdef _WIN32
	Sleep((u64)(seconds * 1000.0));
#endif

#if defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__)
	time_t sec = (time_t)seconds;
	time_t nsec = ((time_t)seconds - sec) * 1000000000L;
	struct timespec req = {
		.tv_sec = sec,
		.tv_nsec = nsec,
	};

	while (nanosleep(&req, &req) == -1) {}
#endif
}
