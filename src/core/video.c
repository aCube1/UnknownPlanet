#include "core/video.h"

#include "common.h"
#include "log.h"

#define DEFAULT_WINDOW_WIDTH  960
#define DEFAULT_WINDOW_HEIGHT 540

Video *video_init(const char *title, const VideoMode *mode) {
	Video *video = xcalloc(1, sizeof(Video));
	memset(video, 0, sizeof(Video));

	if (mode != NULL) {
		video->mode = *mode;

		if (video->mode.width <= 0) {
			video->mode.width = DEFAULT_WINDOW_WIDTH;
		}

		if (video->mode.height <= 0) {
			video->mode.height = DEFAULT_WINDOW_HEIGHT;
		}
	}

	video->window = window_create(title, video->mode.width, video->mode.height);
	if (video->window == NULL) {
		log_fatal("[CORE] - Unable to initialize Video");
		return NULL;
	}

	video->time.previous = get_time();
	return video;
}

void video_quit(Video *video) {
	window_destroy(video->window);

	free(video);
}

void video_clear(Video *video) {
	/* Meansure how many time the frame take to update */
	video->time.current = get_time();
	video->time.update = video->time.current - video->time.previous;
	video->time.previous = video->time.current;

	window_clear(video->window);
}

void video_present(Video *video) {
	window_swapbuffers(video->window);

	/* Meansure how many time the frame take to render */
	video->time.current = get_time();
	video->time.render = video->time.current - video->time.previous;
	video->time.previous = video->time.current;

	/* Get frame delta time */
	video->time.frame = video->time.update + video->time.render;

	/* Wait for some milliseconds... */
	if (video->time.frame < video->mode.fps) {
		wait_time(video->mode.fps - video->time.frame);

		video->time.current = get_time();
		double wait = video->time.current - video->time.previous;
		video->time.previous = video->time.current;

		video->time.frame += wait;
	}
}
