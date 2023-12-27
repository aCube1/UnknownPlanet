#include "core/window.h"
#include "log.h"

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

	window_destroy(window);
	return EXIT_SUCCESS;
}
