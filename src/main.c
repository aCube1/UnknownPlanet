#include "core/engine.h"
#include "core/gfx/render.h"
#include "log.h"

#include <stdlib.h>

#define DEFAULT_WIDTH  960
#define DEFAULT_HEIGHT 540
#define DEFAULT_FPS    60

int main(void) {
	VideoMode mode = {
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
		.fps = 1.0 / DEFAULT_FPS,
	};

	Engine *engine = engine_init("Unknown Planet", &mode);
	if (engine == NULL) {
		log_fatal("Unable to initialize Engine");
		return EXIT_FAILURE;
	}

	while (engine->is_running) {
		render_begin(engine);
		/* Render things here */
		render_end(engine);
	}

	engine_quit(engine);
	return EXIT_SUCCESS;
}
