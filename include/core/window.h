#ifndef _CORE_WINDOW_H_
#define _CORE_WINDOW_H_

#include "types.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

typedef struct VideoMode {
	s32 width;
	s32 height;
	u32 flags; /* Window Flags */
} VideoMode;

typedef struct Window {
	SDL_Window *handler;
	SDL_Renderer *renderer;

	VideoMode mode;

	struct {
		double current;
		double previous;
		double update;     /* Delta time for frame update */
		double render;     /* Delta time for frame render */
		double frame;      /* Delta time for one frame */
		double target;     /* FPS target (set 0 to not apply)*/
		u32 frame_counter; /* FrameCounter */
	} time;
} Window;

Window *window_create(const char *title, const VideoMode *mode);
void window_destroy(Window *window);

void window_clear(Window *window);
void window_present(Window *window);

#endif /* _CORE_WINDOW_H_ */
