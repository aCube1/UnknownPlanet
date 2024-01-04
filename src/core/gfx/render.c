#include "core/gfx/render.h"

#include "core/gfx/opengl.h"
#include "core/glfw/window.h"

void render_begin(Engine *engine) {
	/* Meansure how many time the frame take to update */
	engine->time.current = window_gettime();
	engine->time.update = engine->time.current - engine->time.previous;
	engine->time.previous = engine->time.current;

	gl_clear_color(&engine->clear_color);
	gl_clear_buffers();
}

void render_end(Engine *engine) {
	window_swapbuffers(engine->window);

	/* Meansure how many time the frame take to render */
	engine->time.current = window_gettime();
	engine->time.render = engine->time.current - engine->time.previous;
	engine->time.previous = engine->time.current;

	/* Get frame delta time */
	engine->time.frame = engine->time.update + engine->time.render;

	/* Wait for some milliseconds... */
	if (engine->time.frame < engine->mode.fps) {
		engine_waittime(engine->mode.fps - engine->time.frame);

		engine->time.current = window_gettime();
		double wait = engine->time.current - engine->time.previous;
		engine->time.previous = engine->time.current;

		engine->time.frame += wait;
	}
}
