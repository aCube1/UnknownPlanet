#include "core/window.h"
#include "log.h"

#include <SDL_events.h>
#include <stdlib.h>

#define DEFAULT_WIDTH  960
#define DEFAULT_HEIGHT 540

int main(void) {
	VideoMode mode = {
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
		.flags = 0,
	};

	Window *window = window_create("Unknown Planet", &mode);
	if (window == NULL) {
		log_fatal("Unable to initialize Engine");
		return EXIT_FAILURE;
	}

	bool running = true;
	while (running) {
		SDL_Event events;
		while (SDL_PollEvent(&events) > 0) {
			/* Just check if the window needs to be close */
			switch (events.type) {
			case SDL_QUIT:
				running = false;
				break;
			}
		}

		window_clear(window);
		/* Render things here */
		window_present(window);
	}

	window_destroy(window);
	return EXIT_SUCCESS;
}
