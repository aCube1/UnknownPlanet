#ifndef _CORE_GFX_H_
#define _CORE_GFX_H_

#include "types.h"

typedef void *(*GLLoader)(const char *);

void gl_load(GLLoader loader);

void gl_clear_color(const Color *color);
void gl_clear_buffers(void);

#endif /* _CORE_GFX_H_ */
