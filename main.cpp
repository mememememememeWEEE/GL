#include "glfw3.h"

int main() {
	/* glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); */
	/* glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); */

	GLFWwindow* window;
	if (!glfwInit()) return -1;

	window = glfwCreateWindow(600, 400, "Hello", NULL, NULL);
	if (!window) {glfwTerminate(); return -1;}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		//render here:
		glClear(GL_COLOR_BUFFER_BIT);

		//exchange front and back buffers
		glfwSwapBuffers(window);

		//Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
