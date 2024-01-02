#include "core/time.h"

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

/* Interval = average_time_in_seconds / samples_count */
#define FPS_SAMPLES_COUNT 30
#define FPS_INTERVAL      (0.5f / FPS_SAMPLES_COUNT)

/* Calculate average FPS from Window */
s32 time_getfps(const Time *time) {
	static usize index = 0;
	static float history[FPS_SAMPLES_COUNT] = { 0 };
	static float average = 0;
	static float last = 0;

	if (time->frame == 0.0) {
		return 0;
	}

	/* Only calculate current FPS after some interval */
	if ((get_time() - last) > FPS_INTERVAL) {
		last = (float)get_time();
		index = (index + 1) % FPS_SAMPLES_COUNT;

		average -= history[index];
		history[index] = (float)time->frame / FPS_SAMPLES_COUNT;
		average += history[index];
	}

	return (s32)roundf(1.0F / average);
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

double get_time(void) {
	return (double)SDL_GetTicks64() / 1000.0;
}
