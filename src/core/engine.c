#include "core/engine.h"

#include "common.h"
#include "config.h"
#include "core/glfw/window.h"
#include "log.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef OS_UNIX
#	include <unistd.h>
#elif defined(OS_WINDOWS)
/* NOTE: Declare Sleep() funtion to avoid including 'window.h'.
 * 'kernel32.lib' linkage required. */
__declspec(dllimport) void __stdcall Sleep(u64 msTimeOut);
#endif

#define DEFAULT_WINDOW_WIDTH  960
#define DEFAULT_WINDOW_HEIGHT 540

/* Interval = average_time_in_seconds / samples_count */
#define FPS_SAMPLES_COUNT 30
#define FPS_INTERVAL      (0.5f / FPS_SAMPLES_COUNT)

Engine *engine_init(const char *title, const VideoMode *mode) {
	Engine *engine = xcalloc(1, sizeof(Engine));
	memset(engine, 0, sizeof(Engine));

	if (mode != NULL) {
		engine->mode = *mode;

		if (engine->mode.width <= 0) {
			engine->mode.width = DEFAULT_WINDOW_WIDTH;
		}

		if (engine->mode.height <= 0) {
			engine->mode.height = DEFAULT_WINDOW_HEIGHT;
		}
	}

	engine->window = window_create(title, &engine->mode);
	if (engine->window == NULL) {
		log_fatal("[CORE] - Unable to initialize Window");
		engine_quit(engine);
		return NULL;
	}

	engine->time.previous = window_gettime();
	engine->is_running = true;
	return engine;
}

void engine_quit(Engine *engine) {
	window_destroy(engine->window);

	free(engine);
	engine = NULL;
}

/* Calculate average FPS from Window */
s32 engine_getfps(const Engine *engine) {
	static usize index = 0;
	static float history[FPS_SAMPLES_COUNT] = { 0 };
	static float average = 0;
	static float last = 0;

	if (engine->time.frame == 0.0) {
		return 0;
	}

	/* Only calculate current FPS after some interval */
	if ((window_gettime() - last) > FPS_INTERVAL) {
		last = (float)window_gettime();
		index = (index + 1) % FPS_SAMPLES_COUNT;

		average -= history[index];
		history[index] = (float)engine->time.frame / FPS_SAMPLES_COUNT;
		average += history[index];
	}

	return (s32)roundf(1.0F / average);
}

void engine_waittime(double seconds) {
	double dest_time = window_gettime() + seconds;

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
	while (window_gettime() < dest_time) {}
}
