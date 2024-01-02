#include "core/sdl/window.h"

#include "common.h"
#include "core/gfx/opengl.h"
#include "log.h"

#include <SDL2/SDL.h>

Window *window_create(const char *title, s32 width, s32 height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		log_error("[SDL2] - Unable to initialize: %s", SDL_GetError());
		return NULL;
	}

	/* Set OpenGL context attributes */
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); /* TODO: Change depth buffer size */

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	Window *window = xcalloc(1, sizeof(Window));
	memset(window, 0, sizeof(Window));

	u32 flags = SDL_WINDOW_INPUT_FOCUS;
	flags |= SDL_WINDOW_MOUSE_FOCUS;
	flags |= SDL_WINDOW_MOUSE_CAPTURE;
	flags |= SDL_WINDOW_OPENGL;
	flags |= SDL_WINDOW_SHOWN;

	window->handler = SDL_CreateWindow(
		title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags
	);
	if (window->handler == NULL) {
		log_error("[SDL2] - Cannot create Window: %s", SDL_GetError());
		goto ERROR;
	}

	window->context = SDL_GL_CreateContext(window->handler);
	if (window->context == NULL) {
		log_error("[SDL2] - Cannot create OpenGL context: %s", SDL_GetError());
		goto ERROR;
	}

	/* Load OpenGL extensions */
	gl_load(SDL_GL_GetProcAddress);

	window->clear = (Color) { 0, 0, 0, 255 };
	return window;

ERROR:
	window_destroy(window);
	return NULL;
}

void window_destroy(Window *window) {
	SDL_GL_DeleteContext(window->context);
	SDL_DestroyWindow(window->handler);
	SDL_Quit();

	free(window);
}

void window_clear(Window *window) {
	gl_clear_color(&window->clear);
}

void window_swapbuffers(Window *window) {
	SDL_GL_SwapWindow(window->handler);
}
