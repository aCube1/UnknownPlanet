#ifndef _CORE_SDL_WINDOW_H_
#define _CORE_SDL_WINDOW_H_

#include "types.h"

#include <SDL2/SDL_video.h>

typedef struct Window {
	SDL_Window *handler;
	SDL_GLContext *context;

	Color clear; /* Clear color */
} Window;

Window *window_create(const char *title, s32 width, s32 height);
void window_destroy(Window *window);

void window_clear(Window *window);
void window_swapbuffers(Window *window);

#endif /* _CORE_SDL_WINDOW_H_ */
