#ifndef _CORE_GLFW_WINDOW_H_
#define _CORE_GLFW_WINDOW_H_

#include "core/engine.h"

typedef struct GLFWwindow GLFWwindow;

GLFWwindow *window_create(const char *title, const VideoMode *mode);
void window_destroy(GLFWwindow *window);

void window_swapbuffers(GLFWwindow *window);

double window_gettime(void);

#endif /* _CORE_GLFW_WINDOW_H_ */
