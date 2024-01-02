#include "core/video.h"
#include "log.h"

#include <SDL_events.h>
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

	Video *video = video_init("Unknown Planet", &mode);
	if (video == NULL) {
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

		log_trace("%i -> %f", time_getfps(&video->time), video->time.frame);

		video_clear(video);
		/* Render things here */
		video_present(video);
	}

	video_quit(video);
	return EXIT_SUCCESS;
}
