#include "core/window.h"

#include "common.h"
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
	window->size.width = mode != NULL ? mode->width : 0;
	window->size.height = mode != NULL ? mode->height : 0;
	window->flags = mode != NULL ? mode->flags : 0;

	window->handler = SDL_CreateWindow(
		title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window->size.width,
		window->size.height, window->flags
	);
	if (window->handler == NULL) {
		log_error("[SDL2] - Unable to create Window: %s", SDL_GetError());
		goto ERROR;
	}

	window->renderer = SDL_CreateRenderer(
		window->handler, -1, SDL_RENDERER_TARGETTEXTURE
	);
	if (window->handler == NULL) {
		log_error("[SDL2] - Unable to create Renderer: %s", SDL_GetError());
		goto ERROR;
	}

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
	free(window);
}
