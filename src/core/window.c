#include "core/window.h"

#include "common.h"
#include "core/utils.h"
#include "log.h"

#include <SDL2/SDL.h>

#define INIT_FLAGS (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS)

/* Interval = average_time_in_seconds / samples_count */
#define FPS_SAMPLES_COUNT 30
#define FPS_INTERVAL      (0.5f / FPS_SAMPLES_COUNT)

Window *window_create(const char *title, const VideoMode *mode) {
	if (SDL_Init(INIT_FLAGS) < 0) {
		log_error("[SDL2] - Unable to initialize: %s", SDL_GetError());
		return NULL;
	}

	Window *window = xcalloc(1, sizeof(Window));
	memset(window, 0, sizeof(Window));

	if (mode != NULL) {
		window->mode = *mode;
	}

	window->mode.flags |= SDL_WINDOW_INPUT_FOCUS;
	window->mode.flags |= SDL_WINDOW_MOUSE_FOCUS;
	window->mode.flags |= SDL_WINDOW_MOUSE_CAPTURE;
	window->mode.flags |= SDL_WINDOW_OPENGL;
	window->mode.flags |= SDL_WINDOW_SHOWN;

	window->handler = SDL_CreateWindow(
		title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window->mode.width,
		window->mode.height, window->mode.flags
	);
	if (window->handler == NULL) {
		log_error("[SDL2] - Unable to create Window: %s", SDL_GetError());
		goto ERROR;
	}

	window->renderer = SDL_CreateRenderer(window->handler, -1, SDL_RENDERER_ACCELERATED);
	if (window->renderer == NULL) {
		log_error("[SDL2] - Unable to create Renderer: %s", SDL_GetError());
		goto ERROR;
	}

	window->time.previous = get_time();
	return window;

ERROR:
	window_destroy(window);
	return NULL;
}

void window_destroy(Window *window) {
	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->handler);
	SDL_Quit();

	free(window);
}

void window_clear(Window *window) {
	/* Meansure how many time the frame take to update */
	window->time.current = get_time();
	window->time.update = window->time.current - window->time.previous;
	window->time.previous = window->time.current;

	SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
	SDL_RenderClear(window->renderer);
	SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
}

void window_present(Window *window) {
	SDL_RenderPresent(window->renderer);

	/* Meansure how many time the frame take to render */
	window->time.current = get_time();
	window->time.render = window->time.current - window->time.previous;
	window->time.previous = window->time.current;

	/* Get frame delta time */
	window->time.frame = window->time.update + window->time.render;

	/* Wait for some milliseconds... */
	if (window->time.frame < window->time.target) {
		wait_time(window->time.target - window->time.frame);

		window->time.current = get_time();
		double wait = window->time.current - window->time.previous;
		window->time.previous = window->time.current;

		window->time.frame += wait;
	}
}

void window_set_targetfps(Window *window, s32 fps) {
	window->time.target = fps <= 0 ? 0.0 : 1.0 / fps;
}

/* Calculate average FPS from Window */
s32 window_get_fps(Window *window) {
	static usize index = 0;
	static float history[FPS_SAMPLES_COUNT] = { 0 };
	static float average = 0;
	static float last = 0;

	if (window->time.frame == 0.0) {
		return 0;
	}

	/* Only calculate current FPS after some interval */
	if ((get_time() - last) > FPS_INTERVAL) {
		last = (float)get_time();
		index = (index + 1) % FPS_SAMPLES_COUNT;

		average -= history[index];
		history[index] = (float)window->time.frame / FPS_SAMPLES_COUNT;
		average += history[index];
	}

	return (s32)roundf(1.0F / average);
}
