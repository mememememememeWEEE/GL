#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include <cstdio>
#include <cstdlib>
#include "lib/glew/glew.h"
#include "lib/glfw/glfw3.h"

void error_callback([[maybe_unused]] int error, const char* description) {
	fprintf(stderr, "%s", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

auto MakeWindow(GLFWwindow* window) {
    if (!glfwInit()) {
#ifdef DEBUG
		printf("GLFW initialization failed\n");
#endif
		exit(-1);
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(600, 400, "Hello", NULL, NULL);
	if (!window) {
#ifdef DEBUG
		printf("Window creation failed\n");
#endif
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (glewInit() != GLEW_OK) {
#ifdef DEBUG
		printf("GLEW initialization failed\n");
#endif
		exit(-1);
	}

#ifdef DEBUG
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
#endif

	glViewport(0, 0, 600, 400);
}