#ifndef _CORE_GFX_H_
#define _CORE_GFX_H_

#include "types.h"

typedef struct Color {
	u8 r; /* Red (0 - 255) */
	u8 g; /* Green (0 - 255) */
	u8 b; /* Blue (0 - 255) */
	u8 a; /* Alpha (0 - 255) */
} Color;

typedef void *(*GLLoader)(const char *);

void gl_load(GLLoader loader);

void gl_clear_color(const Color *color);
void gl_clear_buffers(void);

void gl_viewport(s32 x, s32 y, s32 width, s32 height);

#endif /* _CORE_GFX_H_ */
