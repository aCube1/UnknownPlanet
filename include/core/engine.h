#ifndef _CORE_ENGINE_H_
#define _CORE_ENGINE_H_

#include "core/gfx/opengl.h"
#include "types.h"

typedef struct VideoMode {
	s32 width;
	s32 height;
	u32 flags;  /* Window flags */
	double fps; /* Desired frames per second, set 0 to not apply */
} VideoMode;

typedef struct Engine {
	void *window;

	VideoMode mode;
	Color clear_color;

	struct {
		double current;
		double previous;
		double update; /* Delta time for frame update */
		double render; /* Delta time for frame render */
		double frame;  /* Delta time for one frame */
	} time;

	bool is_running;
} Engine;

Engine *engine_init(const char *title, const VideoMode *mode);
void engine_quit(Engine *engine);

s32 engine_getfps(const Engine *engine);
void engine_waittime(double seconds);

#endif /* _CORE_ENGINE_H_ */
