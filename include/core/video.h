#ifndef _CORE_VIDEO_H_
#define _CORE_VIDEO_H_

#include "core/sdl/window.h"
#include "core/time.h"
#include "types.h"

typedef struct VideoMode {
	s32 width;
	s32 height;
	double fps; /* Desired frames per second, set 0 to not apply */
} VideoMode;

typedef struct Video {
	Window *window;

	VideoMode mode;
	Time time;
} Video;

Video *video_init(const char *title, const VideoMode *mode);
void video_quit(Video *video);

void video_clear(Video *video);
void video_present(Video *video);

#endif /* _CORE_VIDEO_H_ */
