#include "core/glfw/window.h"

#include "log.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string.h>

static void error_callback(s32 error, const char *desc);

GLFWwindow *window_create(const char *title, const VideoMode *mode) {
	glfwSetErrorCallback(error_callback);

	if (glfwInit() == GLFW_FALSE) {
		log_error("[GLFW] - Failed to initialize");
		return NULL;
	}

	glfwDefaultWindowHints();
	/* TODO: Handle custom window flags */

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef OS_APPLE
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#else
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
#endif

	GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, title, NULL, NULL);
	if (window == NULL) {
		log_error("[GLFW] - Failed to create Window");
		window_destroy(window);
		return NULL;
	}

	glfwMakeContextCurrent(window);
	if (glfwGetError(NULL) != GLFW_NO_ERROR) {
		log_error("[GLFW] - Failed to initialize Graphics Device");
		window_destroy(window);
		return NULL;
	}

	gl_load((GLLoader)glfwGetProcAddress);

	gl_viewport(0, 0, mode->width, mode->height);
	return window;
}

void window_destroy(GLFWwindow *window) {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void window_swapbuffers(GLFWwindow *window) {
	glfwSwapBuffers(window);
}

double window_gettime(void) {
	return glfwGetTime();
}

static void error_callback(s32 error, const char *desc) {
	log_warn("[GLFW]: %d - %s", error, desc);
}
