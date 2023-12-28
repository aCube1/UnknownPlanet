#include "core/render.h"

#include <SDL_timer.h>

void render_begin(Window *window) {
	if (window == NULL) {
		return;
	}

	window->time.current = time_get();
	window->time.update_delta = window->time.current - window->time.previous;
	window->time.previous = window->time.current;

	SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
	SDL_RenderClear(window->renderer);
	SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
}

void render_end(Window *window) {
	if (window == NULL) {
		return;
	}

	SDL_RenderPresent(window->renderer);

	window->time.current = time_get();
	window->time.render_delta = window->time.current - window->time.previous;
	window->time.previous = window->time.current;
}
