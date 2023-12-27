#ifndef _CORE_WINDOW_H_
#define _CORE_WINDOW_H_

#include "types.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

typedef struct Window {
	SDL_Window *handler;
	SDL_Renderer *renderer;

	u32 flags;

	struct {
		s32 width;
		s32 height;
	} size;
} Window;

typedef struct VideoMode {
	s32 width;
	s32 height;
	u32 flags; /* Window Flags */
} VideoMode;

Window *window_create(const char *title, const VideoMode *mode);
void window_destroy(Window *window);

#endif /* _CORE_WINDOW_H_ */
