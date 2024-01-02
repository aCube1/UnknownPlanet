#include "core/gfx/opengl.h"

#include "log.h"

#include <glad/glad.h>

void gl_load(GLLoader loader) {
	if (gladLoadGLLoader(loader) == 0) {
		log_warn("[GLAD] - Cannot load OpenGL");
	}
}

void gl_clear_color(const Color *color) {
	float red = 0.0F;
	float green = 0.0F;
	float blue = 0.0F;
	float alpha = 1.0F;

	if (color != NULL) {
		/* Clamp colors to the range [0,1] */
		red = (float)color->r / 255;
		green = (float)color->g / 255;
		blue = (float)color->b / 255;
		alpha = (float)color->a / 255;
	}

	glClearColor(red, green, blue, alpha);
}

void gl_clear_buffers(void) {
	glClear(GL_COLOR_BUFFER_BIT);
}
