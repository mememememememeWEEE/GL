#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include <cstdio>
#include "lib/glew/glew.h"
#include "lib/glfw/glfw3.h"

void error_callback([[maybe_unused]] int error, const char* description) {
	fprintf(stderr, "%s", description);
}

int main(void) {
	
	GLFWwindow* window;
	if (!glfwInit()) return -1;

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(600, 400, "Hello", NULL, NULL);
	if (!window) {glfwTerminate(); return -1;}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) return -1;

	while (!glfwWindowShouldClose(window)) {
		//render here:
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		//exchange front and back buffers
		glfwSwapBuffers(window);

		//Poll for and process events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
