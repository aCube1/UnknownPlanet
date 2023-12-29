#include "core/window.h"

#include "common.h"
#include "core/utils.h"
#include "log.h"

#include <SDL2/SDL.h>

#define DEFAULT_INIT_FLAGS \
	(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS)

Window *window_create(const char *title, const VideoMode *mode) {
	if (SDL_Init(DEFAULT_INIT_FLAGS) < 0) {
		log_error("[SDL2] - Unable to initialize: %s", SDL_GetError());
		return NULL;
	}

	Window *window = xcalloc(1, sizeof(Window));

	memset(&window->time, 0, sizeof(window->time));
	if (mode != NULL) {
		window->mode = *mode;
	}

	window->mode.flags |= SDL_WINDOW_OPENGL;
	window->mode.flags |= SDL_WINDOW_SHOWN;
	window->mode.flags |= SDL_WINDOW_INPUT_FOCUS;
	window->mode.flags |= SDL_WINDOW_MOUSE_FOCUS;
	window->mode.flags |= SDL_WINDOW_MOUSE_CAPTURE;

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
	if (window == NULL) {
		return; /* There is nothing to free */
	}

	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->handler);
	SDL_Quit();

	free(window);
}

void window_clear(Window *window) {
	if (window == NULL) {
		return;
	}

	/* Meansure how many time the frame take to update */
	window->time.current = get_time();
	window->time.update = window->time.current - window->time.previous;
	window->time.previous = window->time.current;

	SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
	SDL_RenderClear(window->renderer);
	SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
}

void window_present(Window *window) {
	if (window == NULL) {
		return;
	}

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

	/* Increment FPS counter */
	window->time.frame_counter += 1;
}
